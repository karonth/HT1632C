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


#include <DisplayToolbox.h>
#include "font.h"

///////////////////////////////////////////////////////////////////////////////
//  CTORS & DTOR
//

	DisplayToolbox::DisplayToolbox(MatrixDisplay* _disp)
	{
		// Take reference to display
		disp = _disp;
		// Set the default font
		setFont(FONT_5x7W);
	}

	DisplayToolbox::~DisplayToolbox()
	{
		disp = 0;
	}
	
	
// y, y radius, color
// Shamelessly taken from http://actionsnippet.com/?p=492
void DisplayToolbox::drawCircle(uint8_t xp,uint8_t  yp, uint8_t radius, uint8_t col)
{
  int8_t  balance = 0;
  int8_t xoff = 0;
  int8_t yoff = 0;
  xoff=0;
  yoff=radius;
  balance=- radius;
  while (xoff <= yoff) {
    setPixel(xp+xoff, yp+yoff, col);
    setPixel(xp-xoff, yp+yoff, col);
    setPixel(xp-xoff, yp-yoff, col);
    setPixel(xp+xoff, yp-yoff, col);
    setPixel(xp+yoff, yp+xoff, col);
    setPixel(xp-yoff, yp+xoff, col);
    setPixel(xp-yoff, yp-xoff, col);
    setPixel(xp+yoff, yp-xoff, col);
    if ((balance += xoff++ + xoff)>= 0) 
    {
      balance-=--yoff+yoff;
    }
  }
}


// Bresenham's line function
void DisplayToolbox::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t val )
{
  char deltax = abs(x2 - x1);        // The difference between the x's
  char deltay = abs(y2 - y1);        // The difference between the y's
  char x = x1;                       // Start x off at the first pixel
  char y = y1;                       // Start y off at the first pixel
  char xinc1, xinc2, yinc1, yinc2, den, num, numadd, numpixels, curpixel;

  if (x2 >= x1) {                // The x-values are increasing
    xinc1 = 1;
    xinc2 = 1;
  }  
  else {                          // The x-values are decreasing
    xinc1 = -1;
    xinc2 = -1;
  }

  if (y2 >= y1)                 // The y-values are increasing
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          // The y-values are decreasing
  {
    yinc1 = -1;
    yinc2 = -1;
  }

  if (deltax >= deltay)         // There is at least one x-value for every y-value
  {
    xinc1 = 0;                  // Don't change the x when numerator >= denominator
    yinc2 = 0;                  // Don't change the y for every iteration
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         // There are more x-values than y-values
  }
  else                          // There is at least one y-value for every x-value
  {
    xinc2 = 0;                  // Don't change the x for every iteration
    yinc1 = 0;                  // Don't change the y when numerator >= denominator
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         // There are more y-values than x-values
  }

  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    setPixel(x, y, val);             // Draw the current pixel
    num += numadd;              // Increase the numerator by the top of the fraction
    if (num >= den)             // Check if numerator >= denominator
    {
      num -= den;               // Calculate the new numerator value
      x += xinc1;               // Change the x as appropriate
      y += yinc1;               // Change the y as appropriate
    }
    x += xinc2;                 // Change the x as appropriate
    y += yinc2;                 // Change the y as appropriate
  }
}

// setPixelting function (adds support for multiple displays)
void DisplayToolbox::setPixel(int x, int y, int val, bool paint)
{
  // setPixel
  // Display Number
  // X Cordinate
  // Y Cordinate
  // Value (either on or off, 1, 0)
  // Do you want to write this change straight to the display? (yes: slower)
  disp->setPixel(calcDispNum(x), x, y, val, paint);   
}

// Fetch pixel
// fromShadow - Retrieve from a secondary buffer. 
uint8_t DisplayToolbox::getPixel(int x, int y, bool fromShadow)
{
  return disp->getPixel(calcDispNum(x), x, y, fromShadow);   
}

// Calculate which display x resides and adjust x so it's within the bounds of one display
uint8_t DisplayToolbox::calcDispNum(int& x)
{
  int dispNum = 0;
  if(x >= disp->getDisplayWidth())
  {
    dispNum = x / disp->getDisplayWidth();
    x -= (disp->getDisplayWidth() * dispNum);
  }
  return dispNum;
}

void DisplayToolbox::setBrightness(uint8_t pwmValue)
{
	for(int dispNum=0; dispNum<disp->getDisplayCount(); ++dispNum) disp->setBrightness(dispNum, pwmValue); 
}



void DisplayToolbox::drawRectangle(uint8_t _x, uint8_t _y, uint8_t width, uint8_t height, uint8_t colour, bool filled)
{
	drawLine(_x, _y, _x, _y+height, colour); // Left side of box
	drawLine(_x+width, _y, _x+width, _y+height, colour); // Right side of box
	
	drawLine(_x, _y, _x+width, _y, colour); // top of box
	drawLine(_x, _y+height, _x+width, _y+height, colour); // bottom of box
}


// Choose/change font to use (for next drawChar)
// This corresponds to the list of fonts in font.h
void DisplayToolbox::setFont(uint8_t userfont)
{
  switch(userfont) {

#ifdef FONT_4x6
    case FONT_4x6:
	font = (uint8_t *) &font_4x6[0];
	font_width = 4;
	font_height = 6;
	break;
#endif
#ifdef FONT_5x7
    case FONT_5x7:
	font = (uint8_t *) &font_5x7[0];
	font_width = 5;
	font_height = 7;
	break;
#endif
#ifdef FONT_5x8
    case FONT_5x8:
	font = (uint8_t *) &font_5x8[0];
	font_width = 5;
	font_height = 8;
	break;
#endif
#ifdef FONT_5x7W
    case FONT_5x7W:
	font = (uint8_t *) &font_5x7w[0];
	font_width = 5;
	font_height = 8;
	break;
#endif
#ifdef FONT_6x10
    case FONT_6x10:
	wfont = (prog_uint16_t *) &font_6x10[0];
	font_width = 6;
	font_height = 10;
	break;
#endif
#ifdef FONT_6x12
    case FONT_6x12:
	wfont = (prog_uint16_t *) &font_6x12[0];
	font_width = 6;
	font_height = 12;
	break;
#endif
#ifdef FONT_6x13
    case FONT_6x13:
	wfont = (prog_uint16_t *) &font_6x13[0];
	font_width = 6;
	font_height = 13;
	break;
#endif
#ifdef FONT_6x13B
    case FONT_6x13B:
	wfont = (prog_uint16_t *) &font_6x13B[0];
	font_width = 6;
	font_height = 13;
	break;
#endif
#ifdef FONT_6x13O
    case FONT_6x13O:
	wfont = (prog_uint16_t *) &font_6x13O[0];
	font_width = 6;
	font_height = 13;
	break;
#endif
#ifdef FONT_6x9
    case FONT_6x9:
	wfont = (prog_uint16_t *) &font_6x9[0];
	font_width = 6;
	font_height = 9;
	break;
#endif
#ifdef FONT_7x13
    case FONT_7x13:
	wfont = (prog_uint16_t *) &font_7x13[0];
	font_width = 7;
	font_height = 13;
	break;
#endif
#ifdef FONT_7x13B
    case FONT_7x13B:
	wfont = (prog_uint16_t *) &font_7x13B[0];
	font_width = 7;
	font_height = 13;
	break;
#endif
#ifdef FONT_7x13O
    case FONT_7x13O:
	wfont = (prog_uint16_t *) &font_7x13O[0];
	font_width = 7;
	font_height = 13;
	break;
#endif
#ifdef FONT_7x14
    case FONT_7x14:
	wfont = (prog_uint16_t *) &font_7x14[0];
	font_width = 7;
	font_height = 14;
	break;
#endif
#ifdef FONT_7x14B
    case FONT_7x14B:
	wfont = (prog_uint16_t *) &font_7x14B[0];
	font_width = 7;
	font_height = 14;
	break;
#endif
#ifdef FONT_8x8
    case FONT_8x8:
	font = (uint8_t *) &font_8x8[0];
	font_width = 8;
	font_height = 8;
	break;
#endif
#ifdef FONT_8x13
    case FONT_8x13:
	wfont = (uint16_t *) &font_8x13[0];
	font_width = 8;
	font_height = 13;
	break;
#endif
#ifdef FONT_8x13B
    case FONT_8x13B:
	wfont = (uint16_t *) &font_8x13B[0];
	font_width = 8;
	font_height = 13;
	break;
#endif
#ifdef FONT_8x13O
    case FONT_8x13O:
	wfont = (uint16_t *) &font_8x13O[0];
	font_width = 8;
	font_height = 13;
	break;
#endif
#ifdef FONT_9x15
    case FONT_9x15:
	wfont = (uint16_t *) &font_9x15[0];
	font_width = 9;
	font_height = 15;
	break;
#endif
#ifdef FONT_9x15B
    case FONT_9x15B:
	wfont = (uint16_t *) &font_9x15b[0];
	font_width = 9;
	font_height = 15;
	break;
#endif
#ifdef FONT_8x16
    case FONT_8x16:
	wfont = (uint16_t *) &font_8x16[0];
	font_width = 8;
	font_height = 16;
	break;
#endif
#ifdef FONT_8x16B
    case FONT_8x16B:
	wfont = (uint16_t *) &font_8x16b[0];
	font_width = 8;
	font_height = 16;
	break;
#endif
#ifdef FONT_8x13BK
    case FONT_8x13BK:
	wfont = (uint16_t *) &font_8x13bk[0];
	font_width = 8;
	font_height = 13;
	break;
#endif
  }
}

// Copy a character glyph from the myfont data structure to
// display memory, with its upper left at the given coordinate.
void DisplayToolbox::drawChar(uint8_t x, uint8_t y, char c)
{
  uint16_t dots, msb;
  char col, row;

  if ((unsigned char) c >= 0xc0) c -= 0x41;
  c -= 0x20;
  msb = 1 << (font_height - 1);

  // some math with pointers... don't try this at home ;-)
  prog_uint8_t *addr = font + c * font_width;
  prog_uint16_t *waddr = wfont + c * font_width;

  for (col = 0; col < font_width; col++) {
    dots = (font_height > 8) ? pgm_read_word_near(waddr + col) : pgm_read_byte_near(addr + col);
    for (row = 0; row < font_height; row++) {
      if (dots & (msb >> row))
        setPixel(x+col, y+row, 1);
      else 
        setPixel(x+col, y+row, 0);
      }
    }
}

// Write out an entire string (Null terminated)
uint8_t DisplayToolbox::drawString(int x, int y, char *text, uint8_t dir) {
  uint8_t len = strlen(text);
  uint8_t x_max = disp->getDisplayWidth() * disp->getDisplayCount();
  //uint8_t y_max = disp->getDisplayHeight();
  uint8_t glyph_width = font_width + 1;

  if (dir == CENTER) {  // Note: CENTER ignores the x position and centers across the whole display board(s)
    x = (x_max - glyph_width * len) / 2;
  } else if(dir == RIGHT) {
    x = (x_max + 1 - x - glyph_width * len);
  }

  for(char i=0; i< len; i++)
	{
		drawChar(x, y, text[i]);
		x+=glyph_width; // Width of each glyph
	}

}
