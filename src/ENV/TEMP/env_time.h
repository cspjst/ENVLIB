#ifndef ENV_TIME_H
#define ENV_TIME_H

#include "../../doslib/bioslib/src/BIOS/bios_clock_constants.h"
#include "../../doslib/bioslib/src/BIOS/bios_clock_types.h"

static inline double env_ticks_to_seconds(bios_ticks_since_midnight_t ticks) {
    return ((double)ticks * BIOS_CLOCK_PERIOD);
}

#endif
