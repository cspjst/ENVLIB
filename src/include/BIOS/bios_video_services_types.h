/**
* @author      Jeremy Simon Thornton
* @copyright   2024 Jeremy Simon Thornton
*
*/
#ifndef	BIOS_VIDEO_SERVICES_TYPES
#define BIOS_VIDEO_SERVICES_TYPES

typedef struct {
	unsigned char		columns;
	unsigned char		mode;
	unsigned char		page;
} bios_video_state_t;

typedef struct {
	unsigned char		color_mode;
	unsigned char		ega_memory;
	unsigned char		feature_bits;
	unsigned char		switch_settings;
} bios_video_subsystem_config_t;

#endif
