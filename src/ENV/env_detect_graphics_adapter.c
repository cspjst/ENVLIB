/**
 *
 *  @file      hw_detect_graphics_adapter.c
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.09.2024
 *  @copyright Jeremy Thornton, 2024. All right reserved.
 *
 */
#include "env_detect_graphics_adapter.h"

#include "env_hga_detect_adapter.h"
#include "env_cga_detect_adapter.h"
#include "env_ega_detect_adapter.h"
#include "env_vga_detect_adapter.h"
#include "env_graphics_constants.h"

int env_detect_monochrome_adapter() {
	return env_hga_detect_adapter();   // NB detects MDA adapter too
}

int env_detect_colour_adapter() {
	if (env_vga_detect_adapter()) return ENV_VIDEO_ADAPTER_VGA;
	if (env_ega_detect_adapter()) return ENV_VIDEO_ADAPTER_EGA;
	if (env_cga_detect_adapter()) return ENV_VIDEO_ADAPTER_CGA;
	return ENV_VIDEO_ADAPTER_UKNOWN;;
}
