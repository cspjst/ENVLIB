/**
* @author      Jeremy Simon Thornton
* @copyright   2024 Jeremy Simon Thornton
*
*/
#ifndef	BIOS_VIDEO_SERVICES_CONSTANTS_H
#define BIOS_VIDEO_SERVICES_CONSTANTS_H

#define BIOS_VIDEO_SERVICES                 10h

/**
* BIOS VIDEO SERVICES AH FOR INT 10 - Video BIOS Services
*/

#define BIOS_SET_VIDEO_MODE                     0
//SET_CURSOR_TYPE
#define BIOS_SET_CURSOR_POSITION                2
//READ_CURSOR_POSITION
//READ_LIGHT_PEN
//SELECT_ACTIVE_DISPLAY_PAGE
#define BIOS_SCROLL_ACTIVE_PAGE_UP              06h
#define BIOS_SCROLL_ACTIVE_PAGE_DOWN            07h
//READ_CHARACTER_AND_ATTRIBUTE_AT_CURSOR
//WRITE_CHARACTER_AND_ATTRIBUTE_AT_CURSOR
//WRITE_CHARACTER_AT_CURRENT_CURSOR
//SET_COLOR_PALETTE
//WRITE_GRAPHICS_PIXEL_AT_COORDINATE
//READ_GRAPHICS_PIXEL_AT_COORDINATE
//WRITE_TEXT_IN_TELETYPE_MODE
#define BIOS_GET_CURRENT_VIDEO_STATE            0Fh
//SET/GET_PALETTE_REGISTERS					// (EGA/VGA)
//CHARACTER_GENERATOR_ROUTINE				// (EGA/VGA)
#define BIOS_VIDEO_SUBSYSTEM_CONFIGURATION	    12h	    // (EGA/VGA)
//WRITE_STRING								// (BIOS_AFTER_1/10/86)
//LOAD_LCD_CHAR_FONT						// (CONVERTIBLE)
//RETURN_PHYSICAL_DISPLAY_PARMS				// (CONVERTIBLE)
//VIDEO_DISPLAY_COMBINATION					// (VGA)
//VIDEO_BIOS_STATE_INFORMATION				// (MCGA/VGA)
//SAVE/RESTORE_VIDEO_STATE					// (VGA_ONLY)

//GET_DESQVIEW_VIRTUAL_SCREEN_REGEN_BUFFER
//UPDATE_DESQVIEW_VIRTUAL_SCREEN_REGEN_BUFFER

typedef enum {
    // foreground colours
    BIOS_FG_BLACK           = 0x00,
    BIOS_FG_BLUE            = 0x01,
    BIOS_FG_GREEN           = 0x02,
    BIOS_FG_CYAN            = 0x03,
    BIOS_FG_RED             = 0x04,
    BIOS_FG_MAGENTA         = 0x05,
    BIOS_FG_BROWN           = 0x06,
    BIOS_FG_LIGHT_GREY      = 0x07,
    BIOS_FG_DARK_GREY       = 0x08,
    BIOS_FG_LIGHT_BLUE      = 0x09,
    BIOS_FG_LIGHT_GREEN     = 0x0A,
    BIOS_FG_LIGHT_CYAN      = 0x0B,
    BIOS_FG_LIGHT_RED       = 0x0C,
    BIOS_FG_LIGHT_MAGENTA   = 0x0D,
    BIOS_FG_YELLOW          = 0x0E,
    BIOS_FG_WHITE           = 0x0F,
    // background colours (pre-shifted)
    BIOS_BG_BLACK           = 0x00,
    BIOS_BG_BLUE            = 0x10,
    BIOS_BG_GREEN           = 0x20,
    BIOS_BG_CYAN            = 0x30,
    BIOS_BG_RED             = 0x40,
    BIOS_BG_MAGENTA         = 0x50,
    BIOS_BG_BROWN           = 0x60,
    BIOS_BG_LIGHT_GREY      = 0x70,
    // blink
    BIOS_BLINK              = 0x80
} bios_attr_t;

/**
* BIOS Video Subsytem Configuration Sub-systems:
*/
typedef enum {
    BIOS_RETURN_VIDEO_CONFIGURATION_INFORMATION = 0x10,
    BIOS_SELECT_ALTERNATE_PRINT_SCREEN_ROUTINE = 0x20,
    BIOS_SELECT_SCAN_LINES_FOR_ALPHANUMERIC_MODES = 0x30,
    BIOS_SELECT_DEFAULT_PALETTE_LOADING,
    BIOS_CPU_ACCESS_TO_VIDEO_RAM,
    BIOS_GRAY_SCALE_SUMMING,
    BIOS_CURSOR_EMULATION,
    BIOS_PS2_VIDEO_DISPLAY_SWITCHING,
    BIOS_VIDEO_REFRESH_CONTROL
} bios_video_subsytem_t;

typedef enum {
    BIOS_CGA_TEXT_MONOCHROME_40X25 = 0,              // 00  40x25 B/W text (CGA,EGA,MCGA,VGA)
    BIOS_CGA_TEXT_16_COLOUR_40X25,                   // 01  40x25 16 color text (CGA,EGA,MCGA,VGA)
    BIOS_CGA_TEXT_16_GRAY_80X25,                     // 02  80x25 16 shades of gray text (CGA,EGA,MCGA,VGA)
    BIOS_CGA_TEXT_16_COLOUR_80X25,                   // 03  80x25 16 color text (CGA,EGA,MCGA,VGA)
    BIOS_CGA_GRAPHICS_4_COLOUR_320X200,              // 04  320x200 4 color burst mode CRT/TV graphics (CGA,EGA,MCGA,VGA)
    BIOS_CGA_GRAPHICS_4_GRAY_320X200,                // 05  320x200 4 color RGB graphics (CGA,EGA,MCGA,VGA)
    BIOS_CGA_GRAPHICS_MONOCHROME_640X200,            // 06  640x200 B/W graphics (CGA,EGA,MCGA,VGA)
    BIOS_MDA_TEXT_MONOCHROME_80X25,                  // 07  80x25 Monochrome text (MDA,HERC,EGA,VGA)
    BIOS_PCJR_GRAPHICS_16_COLOUR_160X200,            // 08  160x200 16 color graphics (PCjr)
    BIOS_PCJR_GRAPHICS_16_COLOUR_320X200,            // 09  320x200 16 color graphics (PCjr)
    BIOS_PCJR_GRAPHICS_4_COLOUR_640X200,             // 0A  640x200 4 color graphics (PCjr)
    BIOS_EGA_RESERVED1,                              // 0B  Reserved (EGA BIOS function 11)
    BIOS_EGA_RESERVED2,                              // 0C  Reserved (EGA BIOS function 11)
    BIOS_EGA_GRAPHICS_16_COLOUR_320X200,             // 0D  320x200 16 color graphics (EGA,VGA)
    BIOS_EGA_GRAPHICS_16_COLOUR_640X200,             // 0E  640x200 16 color graphics (EGA,VGA)
    BIOS_EGA_GRAPHICS_MONOCHROME_640X350,            // 0F  640x350 Monochrome graphics (EGA,VGA)
    BIOS_EGA_GRAPHICS_16_COLOUR_640X350,             // 10  640x350 16 color graphics (EGA or VGA with 128K)
    BIOS_MCGA_GRAPHICS_MONOCHROME_640X480,           // 11  640x480 B/W graphics (MCGA,VGA)
    BIOS_VGA_GRAPHICS_16_COLOUR_640X480,             // 12  640x480 16 color graphics (VGA)
    BIOS_MCGA_GRAPHICS_256_COLOUR_320X200            // 13  320x200 256 color graphics (MCGA,VGA)
    /*
    8x  EGA, MCGA or VGA ignore bit 7, see below
    9x  EGA, MCGA or VGA ignore bit 7, see below

    if AL bit 7=1, prevents EGA,MCGA & VGA from clearing display
    N.B. function updates byte at 40:49;  bit 7 of byte 40:87
    */
} bios_video_mode_t;

extern const char bios_video_mode_names[20][64];

#endif
