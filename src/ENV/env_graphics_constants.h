/**
* @author      Jeremy Simon Thornton
* @copyright   2024, 2026 Jeremy Simon Thornton
*
*/
#ifndef ENV_GRAPHICS_CONSTANTS_H
#define ENV_GRAPHICS_CONSTANTS_H

#define ENV_VIDEO_ADAPTER_UKNOWN        0
#define ENV_VIDEO_ADAPTER_MDA           1
#define ENV_VIDEO_ADAPTER_HGA           2
#define ENV_VIDEO_ADAPTER_HGA_PLUS      3
#define ENV_VIDEO_ADAPTER_HGA_INCOLOR   4
#define ENV_VIDEO_ADAPTER_HGA_CLONE     5
#define ENV_VIDEO_ADAPTER_CGA           6
#define ENV_VIDEO_ADAPTER_EGA           7
#define ENV_VIDEO_ADAPTER_MCGA          8
#define ENV_VIDEO_ADAPTER_VGA           9
#define ENV_VIDEO_ADAPTER_SVGA          10

/**
* MDA/HGA and CGA 6845 CRT Controller port numbers.
*/
typedef enum {
    crtc_port_MDA = 0x03B4,
    crtc_port_HGA = 0x03B4,
    crtc_port_CGA = 0x03D4
} env_crtc_port_t;

extern const char ENV_VIDEO_ADAPTER_NAMES[11][32];

#endif
