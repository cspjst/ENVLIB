#ifndef ENV_VERSION_H
#define ENV_VERSION_H

#define ENV_VERSION_MAJOR  0
#define ENV_VERSION_MINOR  0
#define ENV_VERSION_PATCH  2

/**
 * single comparable value: 0xMMmm (major high byte, minor low byte)
 * matches the way DOS reports its own version (major in AH, minor in AL)
 */
#define ENV_VERSION        ((ENV_VERSION_MAJOR << 8) | ENV_VERSION_MINOR)

#define ENV_VERSION_STRING "0.0.2"

#define ENV_MIN_BIOS_VERSION 0x0009

/**
* @brief   Version of ENV.LIB as built.
*
* Packed as 0xMMmm: major in the high byte, minor in the low byte.
* Compare with the ENV_VERSION macro to detect a header/library mismatch.
*/
unsigned int env_version();

/**
* @brief   Full version string of ENV.LIB as built, e.g. "1.2.3".
*
* Includes the patch number, which env_version() omits.
*/
const char* env_version_string();

#endif
