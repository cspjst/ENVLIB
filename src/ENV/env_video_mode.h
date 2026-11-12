/**
 *  @author Jeremy Simon Thornton
 *  @copyright  2026 Jeremy Simon Thornton
 *  @brief  Get and set the BIOS video mode.
 *  @details Thin wrappers over INT 10h functions 00h and 0Fh via BIOSLIB.
 *  Requesting a mode the fitted adapter does not support leaves the current mode unchanged.
 *  NB check with env_get_video_mode()
 */
#ifndef ENV_VIDEO_MODE_H
#define ENV_VIDEO_MODE_H

#include "../include/BIOS/bios_video_services_constants.h"

/**
 * @brief   Set the BIOS video mode (clears the screen).
 * @param   mode  BIOS mode number to select.
 * @return  The mode that was active before the call, for easy restore.
 */
bios_video_mode_t env_set_video_mode(bios_video_mode_t mode);

/**
 * @brief   Get the current BIOS video mode.
 * @return  The active BIOS mode number.
 */
bios_video_mode_t env_get_video_mode();

#endif
