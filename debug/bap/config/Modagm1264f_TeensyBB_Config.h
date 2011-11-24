/*
 * Modagm1264f_Config.h - User specific configuration for Arduino GLCD library
 *
 * vi:ts=4
 *
 * Use this file to set io pins and LCD panel parameters
 * (Combo Teensy/Teensy++ Breadboard configuration)
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


/*********************************************************/
/*  Configuration for LCD panel specific configuration   */
/*********************************************************/
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

// panel controller chips
#define CHIP_WIDTH     64 	// pixels per chip 
#define CHIP_HEIGHT    64	// pixels per chip 

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


/*
 * Bill's Combination BreadBoard pin assignments 
 * for the Teensy or Teensy++ 
 * Using these pins, the teensy and Teensy++ can be
 * interhanged on the breadboard.
 */


/*
 * Pin definitions for Teensy++ v2
 */
#if defined(__AVR_AT90USB1286__)

#define glcd_ConfigName "Bills-BB-v2Teensy++-BGMicro"

#define glcdDI			    PIN_D7
#define glcdRW			    PIN_E0
#define glcdEN			    PIN_E1

#define glcdData0Pin		PIN_C0
#define glcdData1Pin		PIN_C1
#define glcdData2Pin		PIN_C2
#define glcdData3Pin		PIN_C3
#define glcdData4Pin		PIN_C4
#define glcdData5Pin		PIN_C5
#define glcdData6Pin		PIN_C6
#define glcdData7Pin		PIN_C7

// skipped F7 to share config with teensyV2 and avoid LED on V2
#define glcdCSEL1		    PIN_F6
#define glcdCSEL2		    PIN_F5

#define glcdRES 		    PIN_F4

#endif //v2 teensy++ 

/*
 * Pin definitions for Teensy v2
 */
#if defined(__AVR_ATmega32U4__)

#define glcd_ConfigName "Bills-BB-v2Teensy-BGMicro"

#define glcdDI			    PIN_B0
#define glcdRW			    PIN_B1
#define glcdEN			    PIN_B2

#define glcdData0Pin		PIN_B3
#define glcdData1Pin		PIN_B7
#define glcdData2Pin		PIN_D0
#define glcdData3Pin		PIN_D1
#define glcdData4Pin		PIN_D2
#define glcdData5Pin		PIN_D3
#define glcdData6Pin		PIN_C6
#define glcdData7Pin		PIN_C7

// skipped D6 to avoid LED
#define glcdCSEL1		    PIN_D7
#define glcdCSEL2		    PIN_B4

#define glcdRES 		    PIN_B5

#endif // teensy v2

#define glcd_CHIP0	glcdCSEL1,HIGH, glcdCSEL2,LOW
#define glcd_CHIP1	glcdCSEL1,LOW, glcdCSEL2,HIGH

// defines for panel specific timing 
/*
 *	Nov 2009
 *	Low level additions added by Bill Perry
 *	bperrybap@opensource.billsworld.billandterrie.com
 *
 * The following defines are for low level timing.
 * They have been derived from looking at many ks0108 data sheets.
 * Nearly all of the datasheets have the same low level timing.
 * The names used here were derived from the AGM1264F series graphic module.
 * See the data sheet for the exact timing and waveforms.
 * All defines below are in nanoseconds.
 */
#define GLCD_tDDR	320	/* Data Delay time (E high to valid read data) 		*/
#define GLCD_tAS	140	/* Address setup time (ctrl line changes to E high)	*/
#define GLCD_tDSW	200	/* Data setup time (data lines setup to dropping E)	*/
#define GLCD_tWH	450	/* E hi level width (minimum E hi pulse width)		*/
#define GLCD_tWL	450	/* E lo level width (minimum E lo pulse width)		*/


#include "device/ks0108_Device.h"
#endif
