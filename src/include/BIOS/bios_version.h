#ifndef BIOS_VERSION_H
#define BIOS_VERSION_H

#define BIOS_VERSION_MAJOR  0
#define BIOS_VERSION_MINOR  9
#define BIOS_VERSION_PATCH  1

/**
 * single comparable value: 0xMMmm (major high byte, minor low byte)
 * matches the way DOS reports its own version (major in AH, minor in AL)
 */
#define BIOS_VERSION        ((BIOS_VERSION_MAJOR << 8) | BIOS_VERSION_MINOR)

#define BIOS_VERSION_STRING "0.9.1"

/**
* @brief   Version of BIOS.LIB as built.
*
* Packed as 0xMMmm: major in the high byte, minor in the low byte.
* Compare with the BIOS_VERSION macro to detect a header/library mismatch.
*/
unsigned int bios_version();

/**
* @brief   Full version string of BIOS.LIB as built, e.g. "1.2.3".
*
* Includes the patch number, which bios_version() omits.
*/
const char* bios_version_string();

#endif
