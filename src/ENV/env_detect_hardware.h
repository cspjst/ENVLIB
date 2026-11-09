#ifndef ENV_DETECT_HARDWARE_H
#define ENV_DETECT_HARDWARE_H

#include "env_constants.h"

unsigned char env_read_model_byte();

unsigned char env_detect_IBM();

/**
* env_detect_Compaq()
* Compaq was the dominant IBM-compatible manufacturer in the XT/AT era.
* They provided a specific signature for detection.
* Location: 0xF000:0xFF82
* Signature: 3 bytes: 0x0C, 0x48, 0x00
*/

#endif
