/**
* @author      Jeremy Simon Thornton
* @copyright   2026 Jeremy Simon Thornton
*
*/
#ifndef ENV_DETECT_EMULATION_H
#define ENV_DETECT_EMULATION_H

#include "env_constants.h"

/**
 * @brief Scan the ROM BIOS for "DOSBox" starting at FE00:0000 the first 32
 * bytes contain the phrase:
 * "IBM COMPATIBLE 486 BIOS COPYRIGHT The DOSBox Tewm."
 * This seems to be the case for DOSBox itself as well as DOSBox Staging 0.82.2
 * DOSBox-X v2026.01.02 has the phrase "IBM COMPATIBLE BIOS for DOSBox-X" so
 * can detect if a DOSBox based emulator and identify DOSBox-X but not
 * differentiate between DOSBox and DOSBox Staging - at least with this method.
 */
env_emulator_t env_detect_DOSBox();

#endif
