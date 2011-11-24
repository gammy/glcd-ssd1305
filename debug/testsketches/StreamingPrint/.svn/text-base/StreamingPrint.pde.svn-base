/*
 * streaming test
 *
 * Uncomment one of the tests to measure the footprint
 *
 */
  
#include <glcd.h>
#include "fonts/SystemFont5x7.h"       // system font

int width = GLCD.Width;
int height = GLCD.Height;
float pi = 3.14159;

void setup()
{     
  GLCD.Init();   // initialise the library, non inverted writes pixels onto a clear screen
  GLCD.SelectFont(System5x7);
  GLCD.ClearScreen();
 
//  printNormal();           //6276 bytes flash used
  printStreaming();        //6228  
//  printPrintf();           //7156  
  
//  printNormalHex();         //6242 bytes flash used
//  printStreamingHex();      //6234  
  
//  printNormalFloat();      //7606 bytes of flash used
//  printStreamingFloat();   //7602

  
}  

void printNormal()
{
  GLCD.print("width=");
  GLCD.print( width);
  GLCD.print(",");
  GLCD.print(" height=");
  GLCD.println(height);  
}

void printStreaming()
{
  GLCD << "width=" << width << "," << " height=" << height << endl;
}

void printPrintf()
{
  GLCD.Text.Printf("width=%d, height=%d\n", width, height);
}

void printNormalFloat()
{
  GLCD.print("pi = ");
  GLCD.println(pi);     // default float, two decimal places
  GLCD.print("pi = ");
  GLCD.println(pi,5);   // print to 5 decimal places
}

void printStreamingFloat()
{
  GLCD << "pi = " << pi << endl;  // default float, two decimal places
  GLCD << "pi = " << _FLOAT(pi,5) << endl;  // print to 5 decimal places
}

void printNormalHex()
{
  GLCD.print("width=");
  GLCD.print( width);
  GLCD.print(" (");
  GLCD.print(width,HEX);
  GLCD.println(" HEX)"); 
}

void printStreamingHex()
{
  GLCD << "width=" << width << " (" << _HEX(width) << " HEX)" << endl ;  
}

void loop()
{
  
}
