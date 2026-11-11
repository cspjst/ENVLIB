/**
* @author      Jeremy Simon Thornton
* @copyright   2026 Jeremy Simon Thornton
*
*/
#include "env_detect_emulation.h"
#include "env_constants.h"

#include "../MEM/dos_mem_string.h"

env_emulator_t env_detect_DOSBox() {
    void* p = mem_mem(MEM_BLOCK_ROM_BIOS.begin.ptr, SEARCH_SIZE_DOSBOX, SEARCH_DOSBOX, sizeof(SEARCH_DOSBOX));
    if(!p) return DOS_EMULATOR_NONE;
    if(mem_mem(MEM_BLOCK_ROM_BIOS.begin.ptr, SEARCH_SIZE_DOSBOX, SEARCH_DOSBOX_X, sizeof(SEARCH_DOSBOX_X))) {
        return DOS_EMULATOR_DOSBOX_X;
    }
    return DOS_EMULATOR_DOSBOX;
}
