/**
* @author      Jeremy Simon Thornton
* @copyright   2026 Jeremy Simon Thornton
*
*/
#include "../../doslib/src/DOS/dos_memory_types.h"

const dos_mem_block_t MEM_BLOCK_IVT = {(void*)0x00000000, (void*)0x000003FF};
const dos_mem_block_t MEM_BLOCK_BDA = {(void*)0x00400000, (void*)0x004000FF};
const dos_mem_block_t MEM_BLOCK_VIDEO_MONO_PAGE_0 = {(void*)0xB0000000, (void*)0xB0000FFF};
const dos_mem_block_t MEM_BLOCK_VIDEO_COLOUR_PAGE_0 = {(void*)0xB8000000, (void*)0xB8000FFF};
const dos_mem_block_t MEM_BLOCK_ROM_BIOS = {(void*)0xFE000000, (void*)0xF000FFFF};

const char SEARCH_DOSBOX[] = "DOSBox";
const char SEARCH_DOSBOX_X[] = "DOSBox-X";

const char env_names_dosbox[3][32] = {
    "No DOSBox Detected ",
    "DOSBox or Staging ",
    "DOSBox-X "
};

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
const char env_names_ibm_model[11][20] = {
    "Unknown",
    "PC or PCjr late BIOS",     // 80
    "XT or AT late BIOS",       // 86
    "IBM PS/2 (70/80)",         // F8
    "IBM 5140 Convertible",     // F9
    "IBM ps/2 (30/25)",         // FA
    "IBM 5160 XT/2",            // FB
    "IBM 5170 AT",              // FC
    "IBM PCjr",                 // FD
    "IBM 5160 XT",              // FE
    "IBM 5150 PC"               // FF
};
