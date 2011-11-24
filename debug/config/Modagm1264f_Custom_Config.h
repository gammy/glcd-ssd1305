/*
 * Modagm1264f_Custom_Config.h - User specific configuration for Arduino GLCD library
 *
 * Use this file to set io pins and LCD panel parameters
 *
 *	This configuration file is for the AGM1264F module manufactured by AZ Displays.
 *	This module uses 2 ks0108 chips each controlling one half of the display.
 *
 *	This is the 128x64 GLCD that was sold by BGmicro
 *	The datasheet can be downloaded from here:
 *	http://docs.bgmicro.com/pdf/lcd1030.pdf
 *	
 *
 *
 *    <-------------------------------- 128 Pixels -------------------------------->
 *    +--------------------------------------+-------------------------------------+ 
 *    |                                      |                                     | ^
 *    |<------------ 64 Pixels ------------->|                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | 64 pixels
 *    |    Chip 0 controls these pixels      |     Chip 1 Controls these pixels    | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | |
 *    |                                      |                                     | v
 *    +--------------------------------------+-------------------------------------+
 *    |       |20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1|        |
 *    +----------------------------------------------------------------------------+
 *
 *    +-------------------------------------------+
 *    |Pin|Symbol|        Function                | Hook To
 *    +-------------------------------------------+
 *    | 1 | Vss  | Ground                         | Gnd
 *    +-------------------------------------------+
 *    | 2 | Vdd  | +5v (15ma max)                 | +5v ---------------------+
 *    +-------------------------------------------+                          |
 *    | 3 | Vo   | LCD contrast adjust            |--------------------+     |
 *    +-------------------------------------------+                    |     |
 *    | 4 | DI   | H = Data, L=instruction/Status | AVR Pin            |     |
 *    +-------------------------------------------+                    |     |
 *    | 5 | RW   | H = Read, L = Write            | AVR Pin            |     |
 *    +-------------------------------------------+                    |     |
 *    | 6 | E    | Enable signal                  | AVR Pin            |     |
 *    +-------------------------------------------+                    |     |
 *    | 7 | DB0  | Data Bit 0                     | AVR Pin            |     |
 *    +-------------------------------------------+                    |     |
 *    | 8 | DB1  | Data Bit 1                     | AVR Pin            |     |
 *    +-------------------------------------------+                    |     |
 *    | 9 | DB2  | Data Bit 2                     | AVR Pin            |     |
 *    +-------------------------------------------+                    |     |
 *    |10 | DB3  | Data Bit 3                     | AVR Pin      /\/\/\/\/\/\|
 *    +-------------------------------------------+              |  (10-20k)
 *    |11 | DB4  | Data Bit 4                     | AVR Pin      | 
 *    +-------------------------------------------+              | Contrast Pot
 *    |12 | DB5  | Data Bit 5                     | AVR Pin      |
 *    +-------------------------------------------+              |
 *    |13 | DB6  | Data Bit 6                     | AVR Pin      |
 *    +-------------------------------------------+              |
 *    |14 | DB7  | Data Bit 7                     | AVR Pin      |
 *    +-------------------------------------------+              |
 *    |15 | CS1  | H = chip 0 selected            | AVR Pin      |
 *    +-------------------------------------------+              |
 *    |16 | CS2  | H = chip 1 selected            | AVR Pin      |
 *    +-------------------------------------------+              |
 *    |17 | RST  | L = Reset                      | AVR Pin      |
 *    +-------------------------------------------+              |
 *    |18 | VEE  | LCD contrast power supply      |--------------+
 *    +-------------------------------------------+
 *    |19 | BL-  | Backlight -/gnd                | Gnd
 *    +-------------------------------------------+
 *    |20 | BL+  | Backlight + (560ma max)        | 4-10+ ohm Resistor to +5v
 *    +-------------------------------------------+
 *
 */
#ifndef	GLCD_PANEL_CONFIG_H
#define GLCD_PANEL_CONFIG_H

/*
 * define name for configuration
 */
#define glcd_ConfigName "Custom-AGM1264F"

/*********************************************************/
/*  Configuration for LCD panel specific configuration   */
/*********************************************************/
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

// panel controller chips
#define CHIP_WIDTH     64  // pixels per chip
#define CHIP_HEIGHT    64  // pixels per chip

// calculate number of chips & round up if width is not evenly divisable
#define glcd_CHIP_COUNT ((DISPLAY_WIDTH + CHIP_WIDTH - 1)  / CHIP_WIDTH)

/*********************************************************/
/*  Configuration for assigning LCD bits to Arduino Pins */
/*********************************************************/

/*
 * Pins can be assigned using arduino pin numbers 0-n
 * Pins can also be assigned using PIN_Pb 
 *		where P is port A-L and b is bit 0-7
 *		Example: port D pin 3 is PIN_D3
 *
 */


/* Data pin definitions
 */
#define glcdData0Pin		8
#define glcdData1Pin		9
#define glcdData2Pin		10
#define glcdData3Pin		11
#define glcdData4Pin		4
#define glcdData5Pin		5
#define glcdData6Pin		6
#define glcdData7Pin		7

/* Arduino pins used for Commands
 * default assignment uses the first five analog pins
 */
#define glcdCSEL1		14
#define glcdCSEL2		15
// uncomment the following if more than two chip select pins are needed
//#define glcdCSEL3		3   // third chip select line on pin 3 if needed
//#define glcdCSEL4		2   // fourth chip select if needed

#define glcdRW			16
#define glcdDI			17
#define glcdEN			18
// Reset Bit  - uncomment the next line if reset is connected to an output pin
//#define glcdRES	        19	// Reset Bit

/*********************************************************/
/*  Chip Select pin assignments                          */
/*********************************************************/
#define CS_2Chips_2Pins    // default has two chips selected using two pins
//#define CS_2Chips_1Pin   // 2 chips selected using one CS pin (the other CS is inverted in hardware)
//#define CS_3Chips_2Pins  // 3 chips selected using two CS pins
//#define CS_3Chips_3Pins  // 3 chips selected using three CS pins
//#define CS_4Chips_2Pins  // 4 chips selected using two CS pins
//#define CS_4Chips_4Pins  // 4 chips selected using 4 CS pins

/*
 * Two Chip panels using two select pins
 */

#ifdef CS_2Chips_2Pins
#define glcd_CHIP0 glcdCSEL1,HIGH, glcdCSEL2,LOW
#define glcd_CHIP1 glcdCSEL1,LOW, glcdCSEL2,HIGH

/*
 * Two Chip panels using one select pin
 */
 #elif defined  CS_2Chips_1Pin
#define glcd_CHIP0 glcdCSEL1,LOW
#define glcd_CHIP1 glcdCSEL1,HIGH

/*
 * Three Chip panel using two select pins
 */
#elif defined CS_3Chips_2Pins
#define glcd_CHIP0 glcdCSEL1,LOW, glcdCSEL2,HIGH
#define glcd_CHIP1 glcdCSEL1,HIGH, glcdCSEL2,LOW
#define glcd_CHIP2 glcdCSEL1,LOW, glcdCSEL2,LOW

 /*
 * example of three Chip panel using three select pins
 * in this example, the chip is selected by setting a corresponding pin LOW
 *
 * Don't forget that glcdCSEL3 needs to defined (uncommented in the command
pin assignments)
 */
#elif defined CS_3Chips_3Pins
#define glcd_CHIP0 glcdCSEL1,HIGH, glcdCSEL2,LOW,glcdCSEL3,LOW
#define glcd_CHIP1 glcdCSEL1,LOW, glcdCSEL2,HIGH,glcdCSEL3,LOW
#define glcd_CHIP2 glcdCSEL1,LOW, glcdCSEL2,LOW,glcdCSEL3,HIGH
#endif

/*
 * Four Chip panel using four select pins
 *
 * Don't forget that glcdCSEL3 and glcdCSEL4 need to defined
 */
#elif defined CS_4Chips_4Pins
#define glcd_CHIP0 glcdCSEL1,HIGH, glcdCSEL2,LOW, glcdCSEL3, LOW, glcdCSEL4, LOW
#define glcd_CHIP1 glcdCSEL1,LOW, glcdCSEL2,HIGH, glcdCSEL3, LOW, glcdCSEL4, LOW
#define glcd_CHIP2 glcdCSEL1,LOW, glcdCSEL2,LOW, glcdCSEL3, HIGH, glcdCSEL4, LOW
#define glcd_CHIP3 glcdCSEL1,LOW, glcdCSEL2,LOW, glcdCSEL3, LOW, glcdCSEL4, HIGH

/*
 * Four Chip panel using two select pins
 */
#elif defined CS_4Chips_2Pins
#define glcd_CHIP0 glcdCSEL1,LOW, glcdCSEL2,LOW
#define glcd_CHIP1 glcdCSEL1,HIGH, glcdCSEL2,LOW
#define glcd_CHIP2 glcdCSEL1,HIGH, glcdCSEL2,HIGH
#define glcd_CHIP3 glcdCSEL1,LOW, glcdCSEL2,HIGH

/*
 * The following defines are for panel specific low level timing.
 *
 * See your data sheet for the exact timing and waveforms.
 * All defines below are in nanoseconds.
 */

#define GLCD_tDDR	320	/* Data Delay time (E high to valid read data) 		*/
#define GLCD_tAS	140	/* Address setup time (ctrl line changes to E high)	*/
#define GLCD_tDSW	200	/* Data setup time (data lines setup to dropping E)	*/
#define GLCD_tWH	450	/* E hi level width (minimum E hi pulse width)		*/
#define GLCD_tWL	450	/* E lo level width (minimum E lo pulse width)		*/


#include "device/ks0108_Device.h"
#endif //GLCD_PANEL_CONFIG_H
