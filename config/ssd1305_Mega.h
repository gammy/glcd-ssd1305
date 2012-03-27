/*
 * ssd1305_Mega.h - User specific configuration for Arduino GLCD library
 *
 * Use this file to set io pins
 *
 * The configuration below uses a single port for data 
 * and has the same wiring as the mega config from the previous ssd1305 library 
 *
*/

#ifndef GLCD_PIN_CONFIG_H
#define GLCD_PIN_CONFIG_H

/*
 * define name for pin configuration
 */
#define glcd_PinConfigName "ssd1305-Mega"

/*********************************************************/
/*  Configuration for assigning LCD bits to Arduino Pins */
/*********************************************************/
/*
 * Pins used for Commands
 */
#define glcdCSEL1     33    // CS  Bit 
#define glcdRW        35    // R/W Bit
#define glcdDI        36    // D/I Bit 
#define glcdEN        37    // EN Bit

#if NBR_CHIP_SELECT_PINS > 2
#define glcdCSEL3     32   // third chip select if needed
#endif

#if NBR_CHIP_SELECT_PINS > 3
#define glcdCSEL4     41   // fourth chip select if needed
#endif

/*
 * Data pin definitions
 * This version uses pins 22-29 for LCD Data 
 */
#define glcdData0Pin    29
#define glcdData1Pin    28
#define glcdData2Pin    27
#define glcdData3Pin    26
#define glcdData4Pin    25
#define glcdData5Pin    24
#define glcdData6Pin    23
#define glcdData7Pin    22

#define glcdRES         40    // Reset Bit

#endif //GLCD_PIN_CONFIG_H
