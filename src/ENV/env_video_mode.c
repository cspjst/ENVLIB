#include "env_video_mode.h"

#include "../../doslib/bioslib/src/BIOS/bios_video_services.h"

bios_video_mode_t env_set_video_mode(bios_video_mode_t mode) {
    bios_video_state_t old;
    bios_get_video_state(&old);
    bios_set_video_mode(mode);
    return old.mode;
}

bios_video_mode_t env_get_video_mode() {
    bios_video_state_t curr;
    bios_get_video_state(&curr);
    return curr.mode;
}
