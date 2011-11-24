/*
 * GLCDexample (Bills test version)
 *
 * Basic test code for the Arduino GLCD library.
 * This code exercises a range of graphic functions supported
 * by the library and is an example of its use.
 * It also gives an indication of performance, showing the
 * number of frames drawn per second.  
 */


#include <glcd.h>
#include "fonts/Arial14.h"             // proportional font
#include "fonts/SystemFont5x7.h"       // system font
#include "bitmaps/ArduinoIcon64x64.h"  // 64x64 bitmap 
#include "bitmaps/ArduinoIcon64x32.h"

unsigned long startMillis;
unsigned int loops = 0;
unsigned int iter = 0;

 // Create an array of text areas 
 // In a typical app, each text area would be a meaningful named variable
 // that is initialized when its declared 
 // but its an array here to keep the old example logic unchanged

gText textArea[3];

void
PreDefareatest(uint8_t area)
{
	GLCD.ClearScreen();

	textArea[area].DefineArea(textAreaFULL);
	textArea[area].SelectFont(System5x7, BLACK);
	textArea[area].ClearArea();
	textArea[area].print("Full");
	delay(750);
	textArea[area].SelectFont(System5x7, WHITE);
	textArea[area].ClearArea();
	delay(750);

	textArea[area].DefineArea(textAreaTOP);
	textArea[area].SelectFont(System5x7, BLACK);
	textArea[area].ClearArea();
	textArea[area].print("Top");
	delay(750);
	textArea[area].SelectFont(System5x7, WHITE);
	textArea[area].ClearArea();
	delay(750);

	textArea[area].DefineArea(textAreaBOTTOM);
	textArea[area].SelectFont(System5x7, BLACK);
	textArea[area].ClearArea();
	textArea[area].print("Bottom");
	delay(750);
	textArea[area].SelectFont(System5x7, WHITE);
	textArea[area].ClearArea();
	delay(750);

	textArea[area].DefineArea(textAreaLEFT);
	textArea[area].SelectFont(System5x7, BLACK);
	textArea[area].ClearArea();
	textArea[area].print("Left");
	delay(750);
	textArea[area].SelectFont(System5x7, WHITE);
	textArea[area].ClearArea();
	delay(750);

	textArea[area].DefineArea(textAreaRIGHT);
	textArea[area].SelectFont(System5x7, BLACK);
	textArea[area].ClearArea();
	textArea[area].print("Right");
	delay(750);
	textArea[area].SelectFont(System5x7, WHITE);
	textArea[area].ClearArea();
	delay(750);

	textArea[area].DefineArea(textAreaTOPLEFT);
	textArea[area].SelectFont(System5x7, BLACK);
	textArea[area].ClearArea();
	textArea[area].print("TLeft");
	delay(750);
	textArea[area].SelectFont(System5x7, WHITE);
	textArea[area].ClearArea();
	delay(750);

	textArea[area].DefineArea(textAreaTOPRIGHT);
	textArea[area].SelectFont(System5x7, BLACK);
	textArea[area].ClearArea();
	textArea[area].print("TRight");
	delay(750);
	textArea[area].SelectFont(System5x7, WHITE);
	textArea[area].ClearArea();
	delay(750);

	textArea[area].DefineArea(textAreaBOTTOMLEFT);
	textArea[area].SelectFont(System5x7, BLACK);
	textArea[area].ClearArea();
	textArea[area].print("BLeft");
	delay(750);
	textArea[area].SelectFont(System5x7, WHITE);
	textArea[area].ClearArea();
	delay(750);

	textArea[area].DefineArea(textAreaBOTTOMRIGHT);
	textArea[area].SelectFont(System5x7, BLACK);
	textArea[area].ClearArea();
	textArea[area].print("BRight");
	delay(750);
	textArea[area].SelectFont(System5x7, WHITE);
	textArea[area].ClearArea();
	delay(750);
}

void DefRowColtest(void)
{

	GLCD.SetDisplayMode(NON_INVERTED);
	GLCD.ClearScreen(BLACK);
	
	/*
	 * create a 10 column, 4 row text area
	 */
	GLCD.DefineArea(0,0, 10, 4, System5x7);
	GLCD.ClearArea();

	GLCD.print("10x4 chars");
	delay(750);
	GLCD.print("1234567890");
	delay(750);
	GLCD.print("1234567890");
	delay(750);
	GLCD.print("1234567890");

	delay(2000);

	for(uint8_t x = 0; x < 5; x++)
	{
		GLCD.Printf("line%d\n", x);
		delay(750);
	}
	delay(2000);

	/*
	 * Restore default text area
	 */
  	GLCD.DefineArea(textAreaFULL);
}

void testfunc(void)
{

uint8_t a;

	textArea[0].DefineArea(textAreaTOPLEFT);
  	textArea[0].SelectFont(System5x7, BLACK);

	textArea[1].DefineArea(textAreaTOPRIGHT);
  	textArea[1].SelectFont(System5x7, WHITE);

	textArea[2].DefineArea(textAreaBOTTOM);
  	textArea[2].SelectFont(System5x7, BLACK);

	for(a = 0; a < 3; a++)
	{
		textArea[a].CursorTo(0,1);
		textArea[a].Printf("Area: %d", a);
	}

	for(uint8_t y = 0; y < 3; y++)
	{
		for(uint8_t x = 0; x < 100; x++)
		{
			for(a = 0; a < 3; a++)
			{
				/*
				 * Can use overstrike instead of cleararea() with fixed width fonts
				 */
				textArea[a].CursorTo(0,0);
				textArea[a].Printf("a:%d:%d:%02d", a, y,x);
			}
			delay(20);
		}
	}
	delay(2000);
}

void
setup()
{
#ifdef xBAPDEBUG
	Serial.begin(9600);
#ifdef CORE_TEENSY
	delay(500);    // allow USB time to come up.
#endif
bapprintf("Serial initialized\n");

#endif
	delay(5);    // allow the hardware time settle

	
	GLCD.Init();   // initialise the library, non inverted writes pixels onto a clear screen

	testfunc();

	DefRowColtest();
	PreDefareatest(1);

	GLCD.ClearScreen();

	introScreen();
  	scrollingDemo();

	/*
	 * create/restore full display for "default" text area.
	 */
  	GLCD.DefineArea(textAreaFULL);
  	GLCD.SelectFont(System5x7, BLACK);
	GLCD.ClearScreen();
}

void introScreen(){  
  if(GLCD.Height >= 64)   
    GLCD.DrawBitmap(ArduinoIcon64x64, 32,0); //draw the bitmap at the given x,y position
  else
    GLCD.DrawBitmap(ArduinoIcon64x32, 32,0); //draw the bitmap at the given x,y position

  countdown(3);
  GLCD.ClearScreen();
  GLCD.SelectFont(Arial_14); // you can also make your own fonts, see playground for details   
  GLCD.GotoXY(10, 3);
  GLCD.print("GLCD ver ");
  GLCD.print(GLCD_VERSION, DEC);
  GLCD.DrawRoundRect(8,0,GLCD.Width-9,17, 5);  // rounded rectangle around text area   
  countdown(3);  
  GLCD.SelectFont(System5x7, BLACK);
  GLCD.ClearScreen();  
  showCharacters("5x7 font:", System5x7);
  countdown(3);
  showCharacters("Arial_14:", Arial_14);
  countdown(3);
}

void showCharacters(char * title, uint8_t * font)
{
	/*
	 * print title on default text area
	 */
	GLCD.CursorTo(0,0);
	GLCD.print(title);

	/*
	 * Create text area #1
	 */
	textArea[1].SelectFont(font, BLACK);
	textArea[1].DefineArea(GLCD.CenterX + 5, 3, GLCD.Right-2, GLCD.Bottom-4, 1);

	GLCD.DrawRoundRect(GLCD.CenterX + 2, 0, GLCD.CenterX -3, GLCD.Bottom, 5);  // rounded rectangle around text area 

	/*
	 * Dump the text to area #1 with 50ms between chars
	 */
	showAscii(1, 50);
}

void  loop(){   // run over and over again
  iter=0; 
  startMillis = millis();
  while(iter++ < 10){   // do 10 iterations
    GLCD.DrawRect(0, 0, GLCD.CenterX, GLCD.Bottom); // rectangle in left side of screen
    GLCD.DrawRoundRect(GLCD.CenterX + 2, 0, GLCD.CenterX - 3, GLCD.Bottom, 5);  // rounded rectangle around text area   
    for(int i=0; i < GLCD.Bottom; i += 4)
      GLCD.DrawLine(1,1, GLCD.CenterX-1, i);  // draw lines from upper left down right side of rectangle  
    GLCD.DrawCircle(GLCD.CenterX/2, GLCD.CenterY-1, GLCD.CenterY-2);   // draw circle centered in the left side of screen  
    GLCD.FillRect( GLCD.CenterX + GLCD.CenterX/2-8 ,GLCD.CenterY + GLCD.CenterY/2 -8,16,16, WHITE); // clear previous spinner position  
    drawSpinner(loops++, GLCD.CenterX + GLCD.CenterX/2, GLCD.CenterY + GLCD.CenterY/2);       // draw new spinner position
    GLCD.GotoXY(GLCD.CenterX/2, GLCD.Bottom -15); // todo             
    GLCD.print(iter);            // print current iteration at the current cursor position 
  } 
  // display iterations per second
  unsigned long duration = millis() - startMillis;
  int fps = 10000 / duration;
  int fps_fract = (10000 % duration) / 10;
  GLCD.ClearScreen();               // clear the screen  
  //  GLCD.CursorTo(GLCD.CenterX/8 + 1,1);   // position cursor - TODO 
  GLCD.GotoXY(GLCD.CenterX + 4, GLCD.CenterY - 8);
  GLCD.print("FPS=");               // print a text string
  GLCD.print(fps);              
  GLCD.print(".");
  GLCD.print(fps_fract);
}

void showAscii(int area, int _delay)
{
  for( char ch = 0x40; ch < 0x7f; ch++)
  {
    textArea[area].print(ch);
    delay(_delay);
  }   
}

void drawSpinner(byte pos, byte x, byte y) {   
  // this draws an object that appears to spin
  switch(pos % 8) {
    case 0 : GLCD.DrawLine( x, y-8, x, y+8); break;
    case 1 : GLCD.DrawLine( x+3, y-7, x-3, y+7);  break;
    case 2 : GLCD.DrawLine( x+6, y-6, x-6, y+6);  break;
    case 3 : GLCD.DrawLine( x+7, y-3, x-7, y+3);  break;
    case 4 : GLCD.DrawLine( x+8, y, x-8, y);      break;
    case 5 : GLCD.DrawLine( x+7, y+3, x-7, y-3);  break;
    case 6 : GLCD.DrawLine( x+6, y+6, x-6, y-6);  break; 
    case 7 : GLCD.DrawLine( x+3, y+7, x-3, y-7);  break;
  } 
}

void countdown(int count){
  GLCD.SelectFont(System5x7); // select fixed width system font 
  while(count--){  // do countdown  
    GLCD.CursorTo(0,1);   // first column, second row (offset is from 0)
    GLCD.print((char)(count + '0'));
    delay(1000);  
  }  
}

// this function demonstrates scrolling bitmaps and text
void scrollingDemo()
{
  int x;

  GLCD.ClearScreen(WHITE);
  GLCD.SelectFont(System5x7, WHITE); // switch to fixed width system font 
  for(x = 0; x< 32; x++)
  {
    GLCD.FillRect(x, x, 31-x, 31-x, BLACK);
    delay(40);
    GLCD.FillRect(x, x, 31-x, 31-x, WHITE);
  }
  for(x = 31; x; x--)
  {
    GLCD.FillRect(x, x, 31-x, 31-x, BLACK);
    delay(40);
    GLCD.FillRect(x, x, 31-x, 31-x, WHITE);
  }

  for(x = 0; x < 8; x++)
  {
    if(GLCD.Height > 32)
      GLCD.DrawBitmap(ArduinoIcon64x64, x, 0, BLACK);
    else
      GLCD.DrawBitmap(ArduinoIcon64x32, x, x, BLACK);
    delay(50);
  }
  GLCD.ClearScreen();

  for(x = 0; x < 16; x++)
  {
    GLCD.DrawBitmap(ArduinoIcon64x32, GLCD.Width /2 -16 + x, 0, WHITE);
    delay(50);
  }
 
 // gotoxy using default text area  
  textArea[0].SelectFont(Arial_14, WHITE);
  for(x=0; x< 15; x++)
  {
    for(byte p = 0; p < GLCD.Height; p+=8)
    {
      GLCD.DrawHLine(0,p, 8);
    }
    GLCD.GotoXY(x,x);
     GLCD.print("@ABCDFGHIJ");
    delay(200);
    GLCD.ClearScreen();
  }

  // CursorToXY using user defined text area  
  textArea[0].DefineArea(0,0, GLCD.Right,GLCD.Bottom, 1);
  textArea[0].SelectFont(Arial_14, WHITE);
  for(x=0; x< 15; x++)
  {
    for(byte p = 0; p < GLCD.Height; p+=8)
    {
      GLCD.DrawHLine(0,p, 8);
    }
     textArea[0].CursorToXY(x,x);
     textArea[0].print("@ABCDFGHIJ");
    delay(200);
    GLCD.ClearScreen();
  }

  GLCD.ClearScreen();  
  textArea[0].DefineArea(0,0, GLCD.CenterX -1,GLCD.CenterY -1, 1);
  textArea[0].SelectFont(System5x7, WHITE);
  textArea[0].CursorTo(0,0);
  textArea[1].DefineArea(GLCD.CenterX,0, GLCD.Right,GLCD.CenterY-1, -1);
  textArea[1].SelectFont(System5x7, BLACK);
  textArea[1].CursorTo(0,0);
  textArea[2].DefineArea(textAreaBOTTOM,1); 
  
  textArea[2].SelectFont(Arial_14, BLACK);
  textArea[2].CursorTo(0,0);

  for(byte area = 0; area< 3; area++)
  {
    showAscii(area, 80);
  }
  for(char c = 0x20; c < 0x7f; c++)
  {
    for(byte area = 0; area < 3; area++)
    {
       textArea[area].print(c);
    }
    delay(50);
  }  

  for(byte area = 0; area< 3; area++)
  {
     textArea[area].ClearArea();
  }
  for(x = 0; x< 15; x++)
  {
    for(byte area = 0; area < 3; area++)
    {
      // The newline needs to be sent just before the string to make
      // the scrolling look correct. It can be moved below
      // the delay but it won't look as good.
      // if the newline is done while printing the number,
      // you lose a line in the text area because of the scroll
      // and it no longer works with only a 2 line text area.

#ifdef XXX
       textArea[area].print("\nline ");
       textArea[area].print(x);
#else
       textArea[area].print("line ");
       textArea[area].println(x);
#endif
       delay(100);
    }
  }
  textArea[1].ClearArea();
  for(x = 0; x < 16; x++)
  {
    GLCD.DrawBitmap(ArduinoIcon64x32, GLCD.Width/2 -16 + x, 0, WHITE);
    delay(50);
  }
  if(GLCD.Height < 64)
  {
     textArea[0].DefineArea(0,0,GLCD.CenterX-1, GLCD.Bottom-1, 1);
  }

  for(char c = 0x20; c < 0x7f; c++)
  {
    textArea[0].print(c);
    if(GLCD.Height > 32 )
    {    
       textArea[2].print(c);
    }           
    delay(50);
  }
  delay(2000);
}
