/**
* @author      Jeremy Simon Thornton
* @copyright   2024, 2026 Jeremy Simon Thornton
*
*/
#include "env_detect_crtc.h"

int env_detect_crtc(unsigned short port_number) {
    __asm {
        .8086
        pushf

        mov     ax, 0Fh             ; cursor low register
        mov     dx, port_number
        out     dx, al              ; select 6845 cursor low reg
        inc     dx
        in      al, dx              ; AL is old Cursor Low value
        mov     ah, al              ; preserve old value in AH
        mov     al, 66h             ; AL = arbitrary new value
        out     dx, al              ; try to write new value to 6845

        mov     cx, 100h            ; deemed adequate in the literature
WAIT:   loop    WAIT                ; wait for 6845 to respond

        in      al, dx              ; read back value
        xchg    ah, al              ; AL becomes old Cursor Low value
        out     dx, al              ; restore old value

        cmp     ah, 66h             ; test whether 6845 responded with new value?
        mov     ax, 0
        jne     EXIT                ; old value return 0 in AX
        mov     ax, 1               ; new value return 1 in AX

EXIT:   popf
    }
}
