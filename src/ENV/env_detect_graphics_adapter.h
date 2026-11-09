/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.09.2024
 *  @copyright Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef HW_DETECT_GRAPHICS_ADAPTER_H
#define HW_DETECT_GRAPHICS_ADAPTER_H

#include "env_graphics_types.h"

env_adapter_t env_detect_monochrome_adapter();

env_adapter_t env_detect_colour_adapter();

#endif
