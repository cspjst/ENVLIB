#include "env_detect_hardware.h"
#include "env_constants.h"

unsigned char env_read_model_byte() {
    unsigned char id;
    __asm {
        .8086
        push    es

        mov     ax, ROM_BIOS_SEG_END
        mov     es, ax
        mov     al, [es:ROM_BIOS_MODEL_BYTE]
        mov     id, al

        pop     es
    }
    return id;
}

unsigned char env_detect_IBM() {
    unsigned char id = env_read_model_byte();
    if(id >= IBM_MODEL_PS2 && id <=IBM_MODEL_PC)
        return id - IBM_MODEL_PS2 + 3;
    switch(id) {
        case 0x80: return IBM_LATE_PC_JR;
        case 0x86: return IBM_LATE_XT_AT;
        default: return 0;
    }
}
