#include "mda_detect_adapter.h"

#include "../ENV/env_detect_crtc.h"
#include "../ENV/env_graphics_constants.h"

#include "mda_constants.h"

env_adapter_t mda_detect_adapter() {
    env_adapter_t adapter = ENV_VIDEO_ADAPTER_UKNOWN;
    if (env_detect_crtc(crtc_port_MDA)) {
        __asm {
            .8086
            push    ds
            pushf

            mov     dx, MDA_CRTC_STATUS_PORT            ; DX: = 3BAh(MDA/Hercules status port)
            in      al, dx                              ; read status port
            and     al, 80h                             ; mask off only bit 7
            mov     ah, al                              ; copy al into ah = bit 7 (vertical sync on HGC)

            mov     cx, 8000h                           ; 32768 samples - deemed adequate in the literature
    L1:     in      al, dx                              ; read status port
            and     al, 80h                             ; isolate bit 7
            cmp     ah, al                              ; has the vertical sync bit changed?
            loope   L1                                  ; no sample again yes leave loop

            jne     EXIT                                ; bit 7 changed, its not MDA
            mov     adapter, ENV_VIDEO_ADAPTER_MDA      ; MDA

    EXIT:   popf
            pop     ds

        }
    }
    return adapter;
}
