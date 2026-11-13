#ifndef ENV_GRAPHICS_TYPES_H
#define ENV_GRAPHICS_TYPES_H

/**
 * matching the __asm defines in constants file
 */
typedef enum {
    ENV_UNKNOWN,
    ENV_MDA,
    ENV_HGA,
    ENV_HGA_PLUS,
    ENV_HGA_INCOLOR,
    ENV_HGA_CLONE,
    ENV_CGA,
    ENV_EGA,
    ENV_MCGA,
    ENV_VGA,
    ENV_SVGA
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
