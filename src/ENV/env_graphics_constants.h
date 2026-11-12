/**
* @author      Jeremy Simon Thornton
* @copyright   2024, 2026 Jeremy Simon Thornton
*
*/
#ifndef ENV_GRAPHICS_CONSTANTS_H
#define ENV_GRAPHICS_CONSTANTS_H

/**
*  @def   CRTC_STATUS_PORT
*  @brief CRTC Status Register
*  @details This is a read - only register - MDA only two bits of the value read from this port are defined but
*  for a Hercules adapter a third bit (7) is available to read for vertical synchronization.
*  Further, reading from port 03BAh gives Hercules card ID in bits 4-6:
*          03BA
*          ?7?6?5?4?3?2?1?0?
*          ? ? ? ? ? ? ? ? ?
*          ?????????????????  bits
*           ? ? ? ? ? ? ? ???? 0:  H-Sync          0 = off     1 = on
*           ? ? ? ? ? ? ?????? 1:
*           ? ? ? ? ? ???????? 2:
*           ? ? ? ? ?????????? 3:  Current pixel   0 = off     1 = on
*           ? ? ? ???????????? 4:  0?          1?               1?
*           ? ? ?????????????? 5:  0??Hercules 0??Hercules Plus 0??Hercules InColor
*           ? ???????????????? 6:  0?          0?               1?
*           ?????????????????? 7:  V-Sync          0 = *on*    1 = off
*
*/
#define HGA_CRTC_STATUS_PORT        3BAh
#define MDA_CRTC_STATUS_PORT        3BAh
#define CGA_CRTC_STATUS_PORT        3D4h

/**
 * __asm constants
 */
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

extern const char ENV_VIDEO_ADAPTER_NAMES[11][32];

#endif
