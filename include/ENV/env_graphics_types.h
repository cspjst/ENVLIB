#ifndef ENV_GRAPHICS_TYPES_H
#define ENV_GRAPHICS_TYPES_H

#include "env_graphics_constants.h"

/**
 * Video adapter IDs. Values are taken from the ENV_VIDEO_ADAPTER_* __asm
 * constants in env_graphics_constants.h, so C and inline assembly always agree.
 */
typedef enum {
    ENV_UNKNOWN     = ENV_VIDEO_ADAPTER_UKNOWN,
    ENV_MDA         = ENV_VIDEO_ADAPTER_MDA,
    ENV_HGA         = ENV_VIDEO_ADAPTER_HGA,
    ENV_HGA_PLUS    = ENV_VIDEO_ADAPTER_HGA_PLUS,
    ENV_HGA_INCOLOR = ENV_VIDEO_ADAPTER_HGA_INCOLOR,
    ENV_HGA_CLONE   = ENV_VIDEO_ADAPTER_HGA_CLONE,
    ENV_CGA         = ENV_VIDEO_ADAPTER_CGA,
    ENV_EGA         = ENV_VIDEO_ADAPTER_EGA,
    ENV_MCGA        = ENV_VIDEO_ADAPTER_MCGA,
    ENV_VGA         = ENV_VIDEO_ADAPTER_VGA,
    ENV_SVGA        = ENV_VIDEO_ADAPTER_SVGA
} env_video_adapter_t;

/**
* MDA/HGA and CGA 6845 CRT Controller port numbers.
*/
typedef enum {
    ENV_CRTC_PORT_MDA = 0x03B4,
    ENV_CRTC_PORT_HGA = 0x03B4,
    ENV_CRTC_PORT_CGA = 0x03D4
} env_crtc_port_t;

#endif
