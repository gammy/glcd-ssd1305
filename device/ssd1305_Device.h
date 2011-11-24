/*
  ssd1305_Device.h - Arduino library support for graphic LCDs 

 vi:ts=4
  
*/

#ifndef GLCD_PANEL_DEVICE_H
#define GLCD_PANEL_DEVICE_H

/*
 * define name for Device
 */
#define glcd_DeviceName "ssd1305"

/*
 * Sanity check SSD1105 config pins
 *
 *	Help the user detect pin configuration errors by
 *	detecting when defines are missing or are incorrect.
 *
 * [copied directly from ks0108 with no changes]
 */

#if glcd_CHIP_COUNT == 2 && !defined(glcd_CHIP1)
#error "2 chips defined but glcd_CHIP1 chip selects not defined"
#endif

#if glcd_CHIP_COUNT == 3 && !defined(glcd_CHIP2)
#error "3 chips defined but glcd_CHIP2 chip selects not defined"
#endif

#if glcd_CHIP_COUNT == 4 && !defined(glcd_CHIP3)
#error "4 chips defined but glcd_CHIP3 chip selects not defined"
#endif

#if defined(glcd_CHIP3) && glcd_CHIP_COUNT < 4
#error "glcd_CHIP3 defined for less than 4 chips"
#endif

#if defined(glcd_CHIP2) && glcd_CHIP_COUNT < 3
#error "glcd_CHIP2 defined for less than 3 chips"
#endif

#if defined(glcd_CHIP1) && glcd_CHIP_COUNT < 2
#error "glcd_CHIP1 defined for less than 2 chips"
#endif


#if DISPLAY_WIDTH > 255
#warning "Current ssd1305 code only suports up to 255 pixels, downsizing width to 255"
#undef DISPLAY_WIDTH
#define DISPLAY_WIDTH 255
#endif


#ifndef glcdEN
#error "ssd1305 configuration missing glcdEN"
#endif

#ifdef glcdE1
#error "ssd1305 configuration does not use glcdE1"
#endif
#ifdef glcdE2
#error "ssd1305 configuration does not use glcdE2"
#endif

/*
 * LCD commands -------------------------------------------------------------
 */

/* ks0108 
#define LCD_ON				0x3F
#define LCD_OFF				0x3E
#define LCD_SET_ADD			0x40
#define LCD_DISP_START		0xC0
#define LCD_SET_PAGE		0xB8
*/

// ssd1305
#define LCD_ON				0x3F // same as ks0108
#define LCD_OFF				0x3E // same as ks0108
#define LCD_SET_ADD			0x40 // ?? unused? No idea what it's supposed to do.
#define LCD_DISP_START		0x40 // same as ks0713 40h~7Fh - Set Display Start Line
#define LCD_SET_PAGE		0xB0 // same as ks0713 B0h~B7h - Set Page Start Address for Page Addressing Mode 
#define LCD_SET_STARTCOL    0x21

/*
 * Status register bits/flags -----------------------------------------------
 * XXX the ssd1305 doesn't have any status bits apart from "display on/off" on bit 6.
 * See page 72 in the manual.
 */

#define LCD_BUSY_BIT		6
#define LCD_BUSY_FLAG		0x80 

#define LCD_RESET_BIT		4
#define LCD_RESET_FLAG		0x10

/*
 * Define primitives used by glcd_Device.cpp --------------------------------
 */

#define glcd_DevSelectChip(chip) 	SelectChip(chip)

/*
 * KS0108 doesn't use/need a chip # to strobe EN
 * as there is only a single EN line, so ignore the chip parameter.
 */
#define glcd_DevENstrobeHi(chip) lcdfastWrite(glcdEN, 1)
#define glcd_DevENstrobeLo(chip) lcdfastWrite(glcdEN, 0)

/*
 * Convert X & Y coordinates to chip values
 * The macros below assume that chips are either
 * horizontal (normal) or vertical.
 * Horizontal has never been tested and while close
 * the DevXval2ChipCol() macro is currently incorrect for
 * this configuration.
 *
 * If a module does both say for something like a 128x128
 * with 64 pixels each, then the macros below will have
 * to be corrected to acccount for this.
 *
 * While it looks like espensive divides, it will
 * actually map to masking because chip widths/heights
 * on the ks0108 are powers of 2
 */
#if CHIP_HEIGHT < DISPLAY_HEIGHT
#error no no no.
#define glcd_DevXYval2Chip(x,y) ((x/CHIP_WIDTH) + ((y/CHIP_HEIGHT) * (DISPLAY_HEIGHT/CHIP_HEIGHT)))
#else
//#define glcd_DevXYval2Chip(x,y)		((x/CHIP_WIDTH))	
#define glcd_DevXYval2Chip(x,y)		((0))	
#endif

//#define glcd_DevXval2ChipCol(x)		((x) % CHIP_WIDTH)
#define glcd_DevXval2ChipCol(x)		((x))

#endif //GLCD_PANEL_DEVICE_H
