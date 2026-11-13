#include "test_env.h"

#include <stdio.h>
#include <assert.h>

#include "../ENV/env_version.h"
#include "../ENV/env_video_mode.h"
#include "../ENV/env_detect_crtc.h"
#include "../ENV/env_graphics_types.h"
#include "../ENV/env_cga_detect_adapter.h"
#include "../ENV/env_hga_detect_adapter.h"
#include "../ENV/env_mda_detect_adapter.h"

#include "../include/BIOS/bios_version.h"
#include "../include/BIOS/bios_keyboard_services.h"

/* BIOS equipment word 0040:0010, bits 4-5 = initial video mode */
#define EQUIP_VIDEO_MASK  0x30
#define EQUIP_VIDEO_MONO  0x30

#define REPEATS     8
/* standard BIOS modes worth trying (PCjr/Tandy 08h-0Ah left out) */
static const unsigned char candidates[] = {
    0x00, 0x01, 0x02, 0x03,     /* CGA text            */
    0x04, 0x05, 0x06,           /* CGA graphics        */
    0x07,                       /* MDA / Hercules text */
    0x0D, 0x0E, 0x0F, 0x10,     /* EGA graphics        */
    0x11, 0x12, 0x13            /* VGA / MCGA graphics */
};
#define NCANDIDATES (sizeof(candidates) / sizeof(candidates[0]))

static void wait_key(const char* msg) {
    bios_key_t key;
    printf("%s", msg);
    bios_wait_for_keystroke_and_read(&key);
    printf("\n");
}

static int repeatable(unsigned short port) {
    int first = (env_detect_crtc(port) != 0);
    int i;
    for (i = 1; i < REPEATS; ++i) {
        if ((env_detect_crtc(port) != 0) != first) return 0;
    }
    return 1;
}

static unsigned char hga_read_status() {
    unsigned char v;
    __asm {
        mov dx, 0x3BA
        in  al, dx
        mov v, al
    }
    return v;
}

/* count bit-7 (vsync) changes on 3BAh over n reads: 0 = MDA, >0 = Hercules */
static unsigned hga_vsync_toggles(unsigned n) {
    unsigned toggles = 0;
    unsigned char last = hga_read_status() & 0x80;
    unsigned i;
    for (i = 0; i < n; ++i) {
        unsigned char now = hga_read_status() & 0x80;
        if (now != last) { ++toggles; last = now; }
    }
    return toggles;
}

void test_env_detect_crtc() {
    unsigned short equip = *(unsigned short far*)0x00400010L;
    int bios_mono = ((equip & EQUIP_VIDEO_MASK) == EQUIP_VIDEO_MONO);
    int mono;
    int colour;

    printf("Testing ENV CRTC detection...\n");
    printf("BIOS equipment word: %04Xh -> %s display\n", equip, bios_mono ? "mono" : "colour");

    mono   = (env_detect_crtc(ENV_CRTC_PORT_MDA) != 0);
    colour = (env_detect_crtc(ENV_CRTC_PORT_CGA) != 0);
    printf("CRTC at %03Xh (mono):   %s\n", ENV_CRTC_PORT_MDA,   mono   ? "FOUND" : "none");
    printf("CRTC at %03Xh (colour): %s\n", ENV_CRTC_PORT_CGA, colour ? "FOUND" : "none");

    /* the adapter the BIOS booted on must have a CRTC */
    if (bios_mono) assert(mono);
    else           assert(colour);
    printf("Active adapter's CRTC detected: PASS\n");

    /* same answer every time */
    assert(repeatable(ENV_CRTC_PORT_MDA));
    assert(repeatable(ENV_CRTC_PORT_CGA));
    printf("Repeatable over %d probes: PASS\n", REPEATS);

    printf("Expected:\n");
    printf("  MDA/HGA:        3B4h only\n");
    printf("  CGA:            3D4h only\n");
    printf("  EGA/VGA:        the active one (mono or colour)\n");
    printf("  Dual head:      both\n");

    /* cursor must be untouched by probing: ABC and DEF should be contiguous */
    printf("Cursor check: ABC");
    env_detect_crtc(ENV_CRTC_PORT_MDA);
    env_detect_crtc(ENV_CRTC_PORT_CGA);
    printf("DEF\n");
    printf("Line above must read 'Cursor check: ABCDEF' with no gap or jump\n");
    wait_key("Press a key...");

    printf("ENV CRTC detection tests passed\n\n");
}

void test_env_video_mode() {
    unsigned char accepted[NCANDIDATES];
    unsigned char rejected[NCANDIDATES];
    int naccepted = 0;
    int nrejected = 0;
    int i;

    bios_video_mode_t original = env_get_video_mode();
    int mono = (original == BIOS_MDA_TEXT_MONOCHROME_80X25);

    printf("Testing ENV video mode get/set...\n");
    printf("Original mode: %02Xh %s\n", (unsigned)original, bios_video_mode_names[original]);
    printf("Expected accepted modes:\n");
    printf("  MDA/HGA: 07h\n");
    printf("  CGA:     00h-06h\n");
    printf("  EGA:     00h-06h 0Dh-10h\n");
    printf("  VGA:     00h-06h 0Dh-13h\n");
    if (mono) printf("Mono display active: only mode 07h will be tried.\n");
    else      printf("Colour display active: mode 07h will be skipped.\n");
    wait_key("Press a key to start...");

    for (i = 0; i < NCANDIDATES; ++i) {
        bios_video_mode_t mode = (bios_video_mode_t)candidates[i];
        bios_video_mode_t before;
        bios_video_mode_t prev;
        bios_video_mode_t now;

        /* never cross mono <-> colour: the other card may not exist */
        if (mono != (mode == BIOS_MDA_TEXT_MONOCHROME_80X25)) continue;

        before = env_get_video_mode();
        prev = env_set_video_mode(mode);
        assert(prev == before);             /* set returns the previous mode */
        now = env_get_video_mode();

        if (now == mode) {
            accepted[naccepted++] = (unsigned char)mode;
            printf("Mode %02Xh %s\n", (unsigned)mode, bios_video_mode_names[mode]);
            printf("ACCEPTED - check the display looks right\n");
        } else {
            rejected[nrejected++] = (unsigned char)mode;
            printf("Mode %02Xh requested, still %02Xh\n", (unsigned)mode, (unsigned)now);
            printf("REJECTED by BIOS\n");
        }
        wait_key("Press a key...");
    }

    env_set_video_mode(original);
    assert(env_get_video_mode() == original);

    printf("\nRestored mode %02Xh %s\n", (unsigned)original, bios_video_mode_names[original]);
    printf("Accepted:");
    for (i = 0; i < naccepted; ++i) printf(" %02Xh", accepted[i]);
    printf("\nRejected:");
    for (i = 0; i < nrejected; ++i) printf(" %02Xh", rejected[i]);
    printf("\nCompare with the expected list for this adapter.\n");
    printf("ENV video mode tests passed\n\n");
}

void test_env_mda_detect_adapter() {
    env_video_adapter_t result;
    int crtc;
    unsigned toggles = 0;
    int i;

    printf("Testing ENV MDA adapter detection...\n");

    result = env_mda_detect_adapter();
    crtc = (env_detect_crtc(ENV_CRTC_PORT_MDA) != 0);
    if (crtc) toggles = hga_vsync_toggles(32768U);

    printf("env_mda_detect_adapter() = %d (%s)\n", (int)result,
           result == ENV_MDA ? "MDA" : "not MDA");
    printf("CRTC at 3B4h:              %s\n", crtc ? "FOUND" : "none");
    if (crtc) printf("Vsync toggles on 3BAh:     %u\n", toggles);

    /* only two legitimate answers */
    assert(result == ENV_MDA || result == ENV_UNKNOWN);

    /* MDA = mono CRTC present AND no vsync (Hercules toggles bit 7) */
    assert((result == ENV_MDA) == (crtc && toggles == 0));
    printf("Agrees with CRTC probe + vsync sampling: PASS\n");

    /* same answer every time */
    for (i = 1; i < 4; ++i) {
        assert(env_mda_detect_adapter() == result);
    }
    printf("Repeatable over 4 calls: PASS\n");

    printf("Expected:\n");
    printf("  MDA:            MDA\n");
    printf("  Hercules (any): not MDA\n");
    printf("  EGA/VGA mono:   depends on vsync on 3BAh\n");
    printf("  CGA / colour:   not MDA\n");

    printf("ENV MDA adapter detection tests passed\n\n");
}

void test_env_hga_detect_adapter() {
    static const char* names[] = {
        "unknown", "MDA", "Hercules", "Hercules Plus", "Hercules InColor", "Hercules clone"
    };
    env_video_adapter_t result;
    int is_hga;
    int mono_crtc;
    unsigned toggles;
    int i;

    printf("Testing ENV HGA adapter detection...\n");

    result = env_hga_detect_adapter();
    is_hga = (result >= ENV_HGA && result <= ENV_HGA_CLONE);
    printf("env_hga_detect_adapter() = %d (%s)\n", (int)result,
           (result >= ENV_UNKNOWN && result <= ENV_HGA_CLONE) ? names[result] : "OUT OF RANGE");

    /* only unknown or one of the Hercules family */
    assert(result == ENV_UNKNOWN || is_hga);

    /* a Hercules answer needs a CRTC at the mono port */
    mono_crtc = (env_detect_crtc(ENV_CRTC_PORT_HGA) != 0);
    printf("CRTC at 3B4h: %s\n", mono_crtc ? "FOUND" : "none");
    if (is_hga) assert(mono_crtc);

    /* independent vsync check, only meaningful with a mono CRTC present */
    if (mono_crtc) {
        toggles = hga_vsync_toggles(32768U);
        printf("Vsync toggles on 3BAh: %u -> %s\n", toggles, toggles ? "Hercules" : "MDA");
        if (is_hga) assert(toggles > 0);    /* Hercules must show vsync */
        else        assert(toggles == 0);   /* MDA must not             */
        printf("Agrees with vsync sampling: PASS\n");
    }

    /* same answer every time */
    for (i = 1; i < 4; ++i) {
        assert(env_hga_detect_adapter() == result);
    }
    printf("Repeatable over 4 calls: PASS\n");

    printf("Expected:\n");
    printf("  MDA:                unknown\n");
    printf("  Hercules:           Hercules / Plus / InColor / clone per card ID\n");
    printf("  CGA/EGA/VGA colour: unknown\n");

    printf("ENV HGA adapter detection tests passed\n\n");
}

void test_env_cga_detect_adapter() {
    env_video_adapter_t result;
    int crtc;
    int i;

    printf("Testing ENV CGA adapter detection...\n");

    result = env_cga_detect_adapter();
    crtc = (env_detect_crtc(ENV_CRTC_PORT_CGA) != 0);

    printf("env_cga_detect_adapter() = %d (%s)\n", (int)result,
           result == ENV_CGA ? "CGA" : "not CGA");
    printf("CRTC at 3D4h:              %s\n", crtc ? "FOUND" : "none");

    /* only two legitimate answers */
    assert(result == ENV_CGA || result == ENV_UNKNOWN);

    /* CGA = colour CRTC present */
    assert((result == ENV_CGA) == crtc);
    printf("Agrees with CRTC probe: PASS\n");

    /* same answer every time */
    for (i = 1; i < 8; ++i) {
        assert(env_cga_detect_adapter() == result);
    }
    printf("Repeatable over 8 calls: PASS\n");

    printf("Expected:\n");
    printf("  CGA:            CGA\n");
    printf("  MDA/HGA:        not CGA\n");
    printf("  EGA/VGA colour: CGA  (by design - env_detect checks VGA/EGA first)\n");
    printf("  EGA/VGA mono:   not CGA\n");

    printf("ENV CGA adapter detection tests passed\n\n");
}

void test_env() {
    printf("Test ENVLIB...\n");
    assert(bios_version() == ENV_MIN_BIOS_VERSION);
    //test_env_video_mode();
    //test_env_detect_crtc();
    //test_env_cga_detect_adapter();
    //test_env_hga_detect_adapter();
    test_env_mda_detect_adapter();
}
