#include "env_version.h"
#include "../include/BIOS/bios_version.h"

#if BIOS_VERSION < ENV_MIN_BIOS_VERSION
#error vendored BIOSLIB headers incorrect version
#pragma message("found BIOSLIB " BIOS_VERSION_STRING)
#endif

unsigned int env_version() {
    return ENV_VERSION;
}

const char* env_version_string() {
    return ENV_VERSION_STRING;
}
