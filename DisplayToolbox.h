/*
	MatrixDisplay Library
	Author: Zachary Shiner
	Adapted from: Miles Burton, www.milesburton.com/
	Copyright 2013

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DISPLAY_TOOLBOX_GUARD
#define DISPLAY_TOOLBOX_GUARD

#if ARDUINO < 100
#include <WProgram.h>
#include <wiring.h>
#else
#include <Arduino.h>
#endif

#include <MatrixDisplay.h>
#include <avr/pgmspace.h>

/*
This is a utility class, it's purpose to provide several useful functions which maybe used frequently but are not core to the MatrixDisplay operation.

Various code has been shamelessly pinched from around the web, credit added where possible. Please drop me a line if I've used it without permission or forgotten associated credit.
*/

// Font definitions  width x height
// Those commented out are too large for an 8x32 display.
#define FONT_4x6     1
#define FONT_5x7     2
#define FONT_5x8     3
#define FONT_5x7W    4
//#define FONT_6x10    5
//#define FONT_6x12    6
//#define FONT_6x13    7
//#define FONT_6x13B   8
//#define FONT_6x13O   9
//#define FONT_6x9    10
//#define FONT_7x13   11
//#define FONT_7x13B  12
//#define FONT_7x13O  13
//#define FONT_7x14   14
//#define FONT_7x14B  15
#define FONT_8x8    16
//#define FONT_8x13   17
//#define FONT_8x13B  18
//#define FONT_8x13O  19
//#define FONT_9x15   20
//#define FONT_9x15B  21
//#define FONT_8x16   22
//#define FONT_8x16B  23

// Definitions for text position
#define LEFT         0
#define RIGHT        1
#define CENTER       2



class DisplayToolbox
{
private:
	MatrixDisplay* disp;
	uint8_t calcDispNum(int& x);
    uint8_t *font;
    uint16_t *wfont;
	
public:	
	// Constructor
    DisplayToolbox(MatrixDisplay*);
    
	// Destructor
    ~DisplayToolbox();
	
	uint8_t font_width;
    uint8_t font_height;
	
	void drawCircle(uint8_t xp,uint8_t  yp, uint8_t radius, uint8_t col = 1);
	void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t val );
	void setPixel(int x, int y, int val, bool paint = false);
	uint8_t getPixel(int x, int y, bool fromShadow);
	void setBrightness(uint8_t pwmValue);
	void drawRectangle(uint8_t _x, uint8_t _y, uint8_t width, uint8_t height, uint8_t colour, bool filled = false);
	
	void setFont(uint8_t userfont);
	void drawChar(uint8_t x, uint8_t y, char c);
	uint8_t drawString(int x, int y, char *text, uint8_t dir);
};

#endif
