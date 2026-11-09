/**
* @author      Jeremy Simon Thornton
* @copyright   2026 Jeremy Simon Thornton
*
*/
#ifndef DOS_ENVIRONMENT_CONSTANTS_H
#define DOS_ENVIRONMENT_CONSTANTS_H

#include "../../doslib/src/DOS/dos_memory_types.h"

#define ROM_BIOS_SEG_BEGIN   0xFE00
#define ROM_BIOS_OFF_BEGIN   0x0000
#define ROM_BIOS_SEG_END     0xF000
#define ROM_BIOS_OFF_END     0xFFFF

#define ROM_BIOS_MODEL_BYTE  0xFFFE  // IBM hardware using the ROM BIOS Model Byte (2 bytes before the end of the ROM segment)

extern const dos_mem_block_t MEM_BLOCK_IVT;
extern const dos_mem_block_t MEM_BLOCK_BDA;
extern const dos_mem_block_t MEM_BLOCK_VIDEO_MONO_PAGE_0;
extern const dos_mem_block_t MEM_BLOCK_VIDEO_COLOUR_PAGE_0;
extern const dos_mem_block_t MEM_BLOCK_ROM_BIOS;

#define SEARCH_SIZE_DOSBOX  128
extern const char SEARCH_DOSBOX[6];
extern const char SEARCH_DOSBOX_X[8];

typedef enum {
    DOS_EMULATOR_NONE = 0,
    DOS_EMULATOR_DOSBOX,
    DOS_EMULATOR_DOSBOX_X
} env_emulator_t;
extern const char env_names_dosbox[3][32];

/**
 * Machine Identification Byte
 * Model  Sub-Model		Machine
 *  FF	    ??	        Original IBM PC  4/24/81
 *			??	        IBM PC	10/19/81
 *			??	        IBM PC	10/27/82
 *	FE	    ??	        IBM XT (Original)
 *			??	IBM portable PC
 *			??	Compaq DeskPro
 *	FD	    ??	PCjr
 *	FC	    ??	IBM AT (6 MHz)
 *			01	IBM AT 3x9 (8 MHz)
 *			02	IBM XT 286
 *			04	IBM PS/2 Model 50
 *			05	IBM PS/2 Model 60
 *			0B	IBM PS/1
 *	FB	    00	IBM 256/640K XT (aka XT/2)
 *	FA	    00	IBM PS/2 Model 30
 *			01	IBM PS/2 Model 25
 *	F9	    00	IBM PC Convertible
 *	F8	    00	IBM PS/2 Model 80  (16 MHz)
 *			01	IBM PS/2 Model 80  (20 MHz)
 *			04	IBM PS/2 Model 70  (20 MHz)
 *			09	IBM PS/2 Model 70  (16 MHz)
 *	B6	    ??	Hewlett Packard 110
 *	9A	    ??	Compaq Plus
 *	86		    XT (BIOS 11/82+) & AT (BIOS 1/84+) (see note)
 *	80		    PC & PCjr (see note)
 *	2D	    ??	Compaq PC
 *
 * - found at memory location F000:FFFE or via INT 15,C0
 *	- model values of 80 & 86 are returned by BIOS versions previous to the PS/2 but after the BIOS dates marked
 *	- see	INT 15,C0
 */
typedef enum {
    IBM_LATE_PC_JR = 0x80,
    IBM_LATE_XT_AT = 0x86,
    IBM_MODEL_PS2 = 0xF8,
    IBM_PC_CONVERTIBLE,         // 0xF9
    IBM_MODEL_PS2_30,           // 0xFA
    IBM_MODEL_XT_2,             // 0xFB IBM 256/640K XT (aka XT/2)
    IBM_MODEL_AT,               // 0xFC
    IBM_MODEL_PCJR,             // 0xFD
    IBM_MODEL_XT,               // 0xFE
    IBM_MODEL_PC                // 0xFF
} env_ibm_model_id_t;
extern const char env_names_ibm_model[9][20];

#endif
