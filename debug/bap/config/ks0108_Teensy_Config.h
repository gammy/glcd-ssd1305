/*
 * glcd_Teensy_Config.h - User specific configuration for Arduino GLCD library
 *
 * vi:ts=4
 *
 * Use this file to set io pins and LCD panel parameters
 * This version is for a standard ks0108 display
 * connected to a Teesny or Teesny++
 *
 * Note that the Teensy and Teensy++ use different pin numbers 
 * so make sure that your wiring matches the device you are using
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
#define CHIP_WIDTH     64  // pixels per chip
#define CHIP_HEIGHT    64  // pixels per chip

// calculate number of chips & round up if width is not evenly divisable
#define glcd_CHIP_COUNT ((DISPLAY_WIDTH + CHIP_WIDTH - 1)  / CHIP_WIDTH)

/**********************************************************/
/*  Configuration for assigning LCD bits to Teensy++ Pins */
/**********************************************************/
 
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__) // Teensy++

#define glcd_ConfigName "Teensy++ ks0108"   // define name for configuration

#define glcdCSEL1               PIN_E6 
#define glcdCSEL2               PIN_E7
#define glcdRW                  PIN_E0
#define glcdDI                  PIN_E1
#define glcdEN                  PIN_D7
//#define glcdRES		            5	// Reset Bit 

#define glcdData0Pin            PIN_C0
#define glcdData1Pin            PIN_C1
#define glcdData2Pin            PIN_C2
#define glcdData3Pin            PIN_C3
#define glcdData4Pin            PIN_C4
#define glcdData5Pin            PIN_C5
#define glcdData6Pin            PIN_C6
#define glcdData7Pin            PIN_C7

#warning "KS0108 using pins for teensy++"

/*********************************************************/
/*  Configuration for assigning LCD bits to Teensy Pins  */
/*********************************************************/
#elif defined(__AVR_ATmega32U4__)   // Teensy 2.0

#define glcd_ConfigName "Teensy ks0108"   // define name for configuration

#define glcdCSEL1               PIN_D2	// normal connection for control signals
#define glcdCSEL2               PIN_D3
#define glcdRW                  PIN_D1
#define glcdDI                  PIN_D0
#define glcdEN                  PIN_C6
//#define glcdRES		            17	// Reset Bit 

#define glcdData0Pin            PIN_B0
#define glcdData1Pin            PIN_B1
#define glcdData2Pin            PIN_B2
#define glcdData3Pin            PIN_B3
#define glcdData4Pin            PIN_B4
#define glcdData5Pin            PIN_B5
#define glcdData6Pin            PIN_B6
#define glcdData7Pin            PIN_B7

#warning "KS0108 using pins for teensy 2.0"
#endif

/*********************************************************/
/*  Chip Select pin assignments                          */
/*********************************************************/
#define CS_2Chips_2Pins    // default has two chips selected using two pins
//#define CS_3Chips_2Pins  // 3 chips selected using two pins
//#define CS_3Chips_3Pins  // 3 chips selected using three pins

/*
 * Two Chip panels using two select pins
 */

#ifdef CS_2Chips_2Pins
#define glcd_CHIP0 glcdCSEL1,HIGH, glcdCSEL2,LOW
#define glcd_CHIP1 glcdCSEL1,LOW, glcdCSEL2,HIGH

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
