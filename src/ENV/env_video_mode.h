#ifndef ENV_VIDEO_MODE_H
#define ENV_VIDEO_MODE_H

#include "../../doslib/bioslib/src/BIOS/bios_video_services_constants.h"

bios_video_mode_t env_set_video_mode(bios_video_mode_t mode);

bios_video_mode_t env_get_video_mode();

#endif
