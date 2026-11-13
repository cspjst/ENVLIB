#include "env_cga_detect_adapter.h"

#include "env_graphics_constants.h"
#include "env_detect_crtc.h"

env_video_adapter_t env_cga_detect_adapter() {
    if (env_detect_crtc(ENV_CRTC_PORT_CGA)) {
        return ENV_VIDEO_ADAPTER_CGA;
    }
    return ENV_VIDEO_ADAPTER_UKNOWN;
}
