/**
* @author      Jeremy Simon Thornton
* @copyright   2024, 2026 Jeremy Simon Thornton
*
*/
#ifndef ENV_DETECT_CRTC_H
#define ENV_DETECT_CRTC_H

/**
* @brief Detects whether or not a given I/O address is that of a 6845 CRT Controller
* @details The Cursor Location Low register of the alleged CRTC is written with an arbitrary value
* [1] Wilton, Richard, Programmer's Guide to PC and PS/2 Video Systems.
* Wait an arbitrary period of time then check if the value is retained?
* In which case the CRTC is _probably_ detected
*/
unsigned char env_detect_crtc(unsigned short port_number);

#endif
