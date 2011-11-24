/*
/*
  glcd_Device.cpp - Arduino library support for graphic LCDs 

  prototype for Nokia 6610 (uses Gravitech device code) 
  
  vi:ts=4  

  This file is part of the Arduino GLCD library.

  GLCD is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 2.1 of the License, or
  (at your option) any later version.

  GLCD is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with GLCD.  If not, see <http://www.gnu.org/licenses/>.
 
  The glcd_Device class impliments the protocol for sending and receiving data and commands to a GLCD device.
  It uses glcd_io.h to for the io primitives and glcd_COnfig.h for user specific configuration.

*/
#define ENABLE_DEVICE_6610
#ifdef ENABLE_DEVICE_6610
#include <avr/io.h>
#include <wiring.h> // needed for arduino io methods
#include <avr/pgmspace.h>

#include "include/glcd_Device.h"
#include "include/glcd_io.h"

/*
 * define the static variables declared in glcd_Device
 */

uint8_t	 glcd_Device::Inverted; 
lcdCoord  glcd_Device::Coord;

/*
 * colorTable maps 8 bit colors to 16 bit values
 */
 static uint8_t colorTable[] PROGMEM = {
	// red: 3 bit rrr color is mapped to a 5 bit rrrrr color
	0, 4, 9, 13, 18, 22, 27, 31, 0, 0, 0, 0, 0, 0, 0, 0,
	
	// green: 3 bit ggg color is mapped to a 6 bit gggggg color
	0, 9, 18, 27, 36, 45, 54, 63, 0, 0, 0, 0, 0, 0, 0, 0,
	
	// blue: 2 bit bb color is mapped to a 5 bit bbbbb color
	0, 10, 21, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	
	
//#define GLCD_TEENSY_PCB_RESET_WAIT	// turns on code to deal with slow rising reset on Teensy PCB ADAPTER
								// this code is only turned on when library is compiled for teensy boards.
							// The reason for this was to support a ks0108 GLCD adapter PCB for the Teensy.
							// The reset signal created on that board is 250ms long 
							// but rises very slow so reset polling
							// does not work properly. So for now the code simply does a wait of 250ms
							// to give the Teensy PCB reset circuit time to clear.
							//

//#define GLCD_POLL_RESET	// turns on code to poll glcd module RESET signal
							// While this would be optimal, it turns out that on slow
							// rising reset signals to the GLCD the reset bit will clear
							// in the status *before* reset to the actual glcd chips.
							// this creates a situation where the code starts sending commands
							// to the display prior to it being ready. And unfortunately, the first
							// commands sent are to turn on the display. Since the glcd command protocol
							// only has a busy bit, commands appear to work as busy will not be
							// asserted during this reset "grey area". 
							//
							// If you turn this on, additional code will be created to poll reset.
							// and to work with the Teensy GLCD adapter, the blind delay for teensy is disabled
							// and after reset goes away an additional 50ms will be added to work with the
							// Teensy PCB. 
							//
							// When enabled the code is 50+ bytes larger than a dumb/blind wait and it isn't
							// clear if reset polling works the same across all glcds as the datasheets don't
							// fully document how it works.
							//
							// So for now, this is disabled, and the teensy code will get a blind delay 
							// if the RESET_WAIT define above is turned on.


/*
 * This device does not display pixels close to the edge of the display 
 * the following macros converts displayed coordinates to actual device coordinates
 *
 * This may need conditional defines if margins are not the same when the display is flipped (see GLCD_MIRROR_XY)
 */
#define SEND_X_COORD(coord)  sendData(coord + DISPLAY_LEFT_MARGIN) 
#define SEND_Y_COORD(coord)  sendData(coord + DISPLAY_TOP_MARGIN)  
	
glcd_Device::glcd_Device(){
  this->ForeColor = BLACK;
  this->BackColor = WHITE;
}

 /******************************************************/
 /* private functions to send SPI commands and data    */
 /******************************************************/

 /*
  * Bit Bang SPI
  */
static void shiftBits(uint8_t data) 
{
  uint8_t Bit;
  for (Bit = 0; Bit < 8; Bit++)     // 8 Bit Write
  {
	lcdfastWrite(glcdCLK, LOW);
    if((data & 0x80) >> 7 )
    {
		lcdfastWrite(glcdSDA, HIGH);
    }
    else
    {
		lcdfastWrite(glcdSDA, LOW);
    }
	lcdfastWrite(glcdCLK, HIGH);  // Strobe signal bit 

    data <<= 1;   // Next bit data
  }  
}

 /*
  * private function to send a Command   
  */
static void sendCMD(uint8_t cmd) 
{
  lcdfastWrite(glcdCS, HIGH);
  lcdfastWrite(glcdCLK, LOW);
  lcdfastWrite(glcdCS, LOW);
  lcdfastWrite(glcdSDA, LOW);
  lcdfastWrite(glcdCLK, HIGH);
  lcdfastWrite(glcdCLK, LOW);

  shiftBits(cmd);
  lcdfastWrite(glcdCLK, LOW);
  lcdfastWrite(glcdCS, HIGH);
}

 /*
  * private function to send data
  */
static void sendData(uint8_t data) 
{
  lcdfastWrite(glcdCS, HIGH);
  lcdfastWrite(glcdCLK, LOW);
  lcdfastWrite(glcdCS, LOW);
  lcdfastWrite(glcdSDA, HIGH);
  lcdfastWrite(glcdCLK, HIGH);
  lcdfastWrite(glcdCLK, LOW);

  shiftBits(data);
  lcdfastWrite(glcdCLK, LOW);
  lcdfastWrite(glcdCS, HIGH);
}

 
/**
 * set pixel at x,y to the given color
 *
 * @param x X coordinate, a value from 0 to GLCD.Width-1
 * @param y Y coordinate, a value from 0 to GLCD.Heigh-1
 * @param color WHITE or BLACK
 *
 * Sets the pixel at location x,y to the specified color.
 * x and y are relative to the 0,0 origin of the display which
 * is the upper left corner.
 * Requests to set pixels outside the range of the display will be ignored.
 *
 * @note If the display has been set to INVERTED mode then the colors
 * will be automically reversed.
 *
 */

void glcd_Device::SetDot(uint8_t x, uint8_t y, uint8_t color) 
{
	if((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT))
		return;
	
	this->GotoXY(x, y);	
	sendCMD(LCD_RAMWR);
	sendData(color);
	//sendCMD(LCD_NOP);  // any command turns if RAM Write mode, this may not be needed
}

/**
 * set an area of pixels
 *
 * @param x X coordinate of upper left corner
 * @param y Y coordinate of upper left corner
 * @param x2 X coordinate of lower right corner
 * @param y2 Y coordinate of lower right corner
 * @param color
 *
 * sets the pixels an area bounded by x,y to x2,y2 inclusive
 * to the specified color.
 *
 * The width of the area is x2-x + 1. 
 * The height of the area is y2-y+1 
 * 
 *
 */

// set pixels from upper left edge x,y to lower right edge x1,y1 to the given color
// the width of the region is x1-x + 1, height is y1-y+1 

void glcd_Device::SetPixels(uint8_t x, uint8_t y,uint8_t x2, uint8_t y2, uint8_t color)
{
  uint8_t xmin, xmax, ymin, ymax;
  uint16_t i;
  
  // best way to create a filled rectangle is to define a drawing box
  // calculate the min and max for x and y directions
  xmin = (x <= x2) ? x : x2;
  xmax = (x > x2)  ? x : x2;
  ymin = (y <= y2) ? y : y2;
  ymax = (y > y2)  ? y : y2;

  // specify the controller drawing box according to those limits
  // Row address set (command 0x2B)
  sendCMD(LCD_CASET);
  SEND_X_COORD(xmin);
  SEND_X_COORD(xmax);

  // Column address set (command 0x2A)
  sendCMD(LCD_PASET);
  SEND_Y_COORD(ymin);
  SEND_Y_COORD(ymax);

  // WRITE MEMORY
  sendCMD(LCD_RAMWR);

  // loop on total number of pixels 
  for (i = 0; i < ((xmax - xmin + 1) * (ymax - ymin + 1)) ; i++) 
  {
    sendData(color);
  }
  //sendCMD(LCD_NOP);  // ensure RAM Write mode is terminated
}

/**
 * set current x,y coordinate on display device
 *
 * @param x X coordinate
 * @param y Y coordinate
 *
 * Sets the current pixel location to x,y.
 * x and y are relative to the 0,0 origin of the display which
 * is the upper left most pixel on the display.
 */

void glcd_Device::GotoXY(uint8_t x, uint8_t y)
{

#ifndef GLCD_READDATA_ORIG
	if((x == this->Coord.x) && (y == this->Coord.y))
		return;
#endif

	if( (x > DISPLAY_WIDTH-1) || (y > DISPLAY_HEIGHT-1) )	// exit if coordinates are not legal  
	{
	  return;
	}

	this->Coord.x = x;								// save new coordinates
	this->Coord.y = y;

	// Row address set 
	sendCMD(LCD_PASET);
	SEND_Y_COORD(y);
	SEND_Y_COORD(y);

	// Column address set 
	sendCMD(LCD_CASET);
	SEND_X_COORD(x);
	SEND_X_COORD(x);
}
/**
 * Low level h/w initialization of display and AVR pins
 *
 * @param invert specifices whether display is in normal mode or inverted mode.
 *
 * This should only be called by other library code.
 *
 * It does all the low level hardware initalization of the display device.
 *
 * The optional invert parameter specifies if the display should be run in a normal
 * mode, dark pixels on light background or inverted, light pixels on a dark background.
 *
 * To specify dark pixels use the define @b NON-INVERTED and to use light pixels use
 * the define @b INVERTED
 *
 * Upon completion of the initialization, the entire display will be cleared
 * and the x,y postion will be set to 0,0
 *
 */

/*
 * Note: This Initilization code can be called more than once as the user
 * is free to re-initliaze the hardware.
 */

 void glcd_Device::Init(uint8_t invert)
{  
	/*
	 * Now setup the pinmode for all of our control pins.
	 */
  DDRD |= B01111100;   // Set SPI pins as output 
  PORTD |= B01111100;  // Set SPI pins HIGH
/*	 
	lcdPinMode(glcdBL,OUTPUT);   
	lcdPinMode(glcdCS,OUTPUT);   
	lcdPinMode(glcdCLK,OUTPUT);  
	lcdPinMode(glcdSDA,OUTPUT);  
	lcdPinMode(glcdRESET,OUTPUT);
	
	// set pins high
	lcdfastWrite(glcdBL,HIGH);   
	lcdfastWrite(glcdCS,HIGH);   
	lcdfastWrite(glcdCLK,HIGH);  
	lcdfastWrite(glcdSDA,HIGH); 
    lcdfastWrite(glcdRESET,HIGH); 	
*/
	this->Coord.x = 0;
	this->Coord.y = 0;
	
	this->Inverted = invert;
	 // Initial state

	lcdfastWrite(glcdCLK, LOW);
	lcdfastWrite(glcdCS, HIGH);
	lcdfastWrite(glcdSDA, HIGH);
	
	/*
	 * Reset the glcd module 
	 */ 	 
	lcdReset();
	delay(30);
	lcdDelayNanoseconds(GLCD_tWres);  
	lcdUnReset();
	delay(30);
	lcdDelayMilliseconds(GLCD_tRT);

#if defined(GLCD_TEENSY_PCB_RESET_WAIT) && defined(CORE_TEENSY) && !defined(GLCD_POLL_RESET)
	/*
	 * Delay for Teensy ks0108 PCB adapter reset signal
	 * Reset polling is not realiable by itself so this is easier and much less code
	 * - see long comment above where GLCD_POLL_RESET is defined
	 */
	lcdDelayMilliseconds(250);
#endif
	
	// Turn Sleep off
	sendCMD(LCD_SLEEPOUT);
	
	sendCMD(LCD_INVOFF); 
	
	// RGB Color Interface Pixel Format
	sendCMD(LCD_COLMOD);
	sendData(0x02);    // 0x02 = 8 bits-per-pixel
	
	// send pixel color palette
	sendCMD(LCD_RGBSET);
	for(uint8_t i=0; i < sizeof(colorTable) /sizeof(uint8_t); i++){
		sendData(pgm_read_byte(colorTable + i));
	}  
	sendCMD(LCD_NOP);
	
	// Memory access controler 
	sendCMD(LCD_MADCTL);
#if defined GLCD_MIRROR_XY	
	sendData(0xC0);  // 0xC0 = mirror x and y
#else
	sendData(0x00);  // 0x00 = defualt memory access configuration	
#endif

	// Write contrast 
	sendCMD(LCD_SETCON);
	sendData(0x30); // contrast 0x30
	lcdDelayMilliseconds(100);

     // Display On 
	sendCMD(LCD_DISPON);

	/*
	 * All hardware initialization is complete.
	 *
	 * Now, clear the screen and home the cursor to ensure that the display always starts
	 * in an identical state after being initialized.
	 *
	 * Note: the reason that SetPixels() below always uses WHITE, is that once the
	 * the invert flag is in place, the lower level read/write code will invert data
	 * as needed.
	 * So clearing an areas to WHITE when the mode is INVERTED will set the area to BLACK
	 * as is required.
	 */
	 
    this->SetPixels(0,0, DISPLAY_WIDTH-1,DISPLAY_HEIGHT-1, WHITE);
	this->GotoXY(0,0);
}

#ifdef glcd_CHIP0  // if at least one chip select string
__inline__ void glcd_Device::SelectChip(uint8_t chip)
{  
  // not supported
}
#endif

void glcd_Device::WaitReady( uint8_t chip)
{
	// wait until LCD busy bit goes to zero
	// not supported
}

#ifdef GLCD_POLL_RESET
void glcd_Device::WaitReset( uint8_t chip)
{
	// not supported

}
#endif

/**
 * read a data byte from display device memory
 *
 * THIS VERSION ALWAYS RETURNS 0, the 6610 board does not support read
 * 
 * @return the data byte at the current x,y position
 *
 * @note the current x,y location is not modified by the routine.
 *	This allows a read/modify/write operation.
 *	Code can call ReadData() modify the data then
 *  call WriteData() and update the same location.
 *
 * @see WriteData()
 */
 uint8_t glcd_Device::ReadData()
{  
    // not supported
	return 0;
}

void glcd_Device::WriteCommand(uint8_t cmd, uint8_t chip)
{
    sendCMD(cmd); // 6610 only has one chip
}


/**
 * Write a byte to display device memory
 *
 * note that this version assumes that a byte of data is a 8 vertical pixels
 * with the top pixel at the current xy coordinates 
 *
 */

void glcd_Device::WriteData(uint8_t data) {
	//showHex("wrData",data);
    //showXY("wr", this->Coord.x,this->Coord.y);

#ifdef GLCD_DEBUG
	volatile uint16_t i;
	for(i=0; i<5000; i++);
#endif

	if(this->Coord.x >= DISPLAY_WIDTH){
		return;
	}
    // specify a drawing box at x,y that is 8 pixels high
	// Row address set 
	sendCMD(LCD_CASET);
	SEND_X_COORD(this->Coord.x);
	SEND_X_COORD(this->Coord.x);

	// Column address set 
	sendCMD(LCD_PASET);
	SEND_Y_COORD(this->Coord.y);
	SEND_Y_COORD(this->Coord.y + 7); // the controller will ignore invalid pixels 

	// WRITE MEMORY
	sendCMD(LCD_RAMWR);
	// loop on total number of pixels 
	for (uint8_t i = 0; i < 8 ; i++)
	{
        if(data & 1 << i )
			sendData(this->ForeColor) ; 
		else
           sendData(this->BackColor) ;		
	}
	sendCMD(LCD_NOP);  // ensure RAM Write mode is terminated
	
	this->Coord.x++;
}

/*
 * needed to resolve virtual print functions
 */
void glcd_Device::write(uint8_t) // for Print base class
{

}
#endif //  ENABLE_DEVICE_6610
