
#include "glcd.h"
//#include "fonts/fixednums15x31.h"
//#include "fonts/fixednums8x16.h"
//#include "fonts/fixednums7x15.h"
//#include "fonts/SystemFont5x7.h"
#include "fonts/allFonts.h"

void setup() {
	GLCD.Init(NON_INVERTED);
}

gText t1;
gText t2;
void loop()
{
uint8_t hr, min, sec;
int counter = 0;;


//	GLCD.SelectFont(fixednums8x16);
	GLCD.SelectFont(fixednums15x31);

	t1.DefineArea(textAreaBOTTOM);
	t1.SelectFont(fixednums8x16);

	hr = 0;
	min = 0;
	sec = 0;
	while(1)
	{
#if DISPLAY_WIDTH > 127
		GLCD.CursorToXY(0,0);
		GLCD.Printf("%02d:%02d.%02d", hr, min, sec);
#if DISPLAY_HEIGHT > 32
		t1.CursorTo(0,0);
		t1.SelectFont(fixednums8x16);
		t1.Printf("%02d:%02d.%02d", hr, min, sec);
		t1.SelectFont(fixednums7x15);
		t1.CursorTo(0,1);
		t1.Printf("%02d:%02d.%02d", hr, min, sec);
#endif
		sec++; // not really seconds but animates display
		if(sec > 59)
		{
			sec = 0;
			min++;
			if(min>59)
			{
				min = 0;
				hr++;
				if(hr>11)
					hr = 0;
			}
		}
#else
		GLCD.CursorTo(0,0);
		GLCD.Printf("%04d", counter);
		counter++;
		delay(100);
#endif
	}
}
