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

#ifndef MATRIX_DISPLAY_GUARD
#define MATRIX_DISPLAY_GUARD

#if ARDUINO < 100
#include <WProgram.h>
#include <wiring.h>
#else
#include <Arduino.h>
#endif


/*
	All the various commands for HT1623C
*/
#define HT1632_ID_CMD 4		/* ID = 100 - Commands */
#define HT1632_ID_RD  6		/* ID = 110 - Read RAM */
#define HT1632_ID_WR  5		/* ID = 101 - Write RAM */

#define HT1632_CMD_SYSDIS 0x00	/* CMD= 0000-0000-x Turn off oscil - DEFAULT */
#define HT1632_CMD_SYSON  0x01	/* CMD= 0000-0001-x Enable system oscil */
#define HT1632_CMD_LEDOFF 0x02	/* CMD= 0000-0010-x LED duty cycle gen off - DEFAULT */
#define HT1632_CMD_LEDON  0x03	/* CMD= 0000-0011-x LEDs ON */
#define HT1632_CMD_BLOFF  0x08	/* CMD= 0000-1000-x Blink OFF */
#define HT1632_CMD_BLON   0x09	/* CMD= 0000-1001-x Blink On */
#define HT1632_CMD_SLVMD  0x10	/* CMD= 0001-00xx-x Slave Mode - external clock & sync */
#define HT1632_CMD_MSTMD  0x18	/* CMD= 0001-10xx-x Master Mode - on-chip clock & sync - DEFAULT */
#define HT1632_CMD_EXTCLK 0x1C	/* CMD= 0001-11xx-x Use external clock only */
#define HT1632_CMD_COMS00 0x20	/* CMD= 0010-ABxx-x AB=00: N-MOS  8-COMMON - DEFAULT */
#define HT1632_CMD_COMS01 0x24	/* CMD= 0010-ABxx-x AB=01: N-MOS 16-COMMON */
#define HT1632_CMD_COMS10 0x28	/* CMD= 0010-ABxx-x AB=10: P-MOS  8-COMMON */
#define HT1632_CMD_COMS11 0x2C	/* CMD= 0010-ABxx-x AB=11: P-MOS 16-COMMON */
#define HT1632_CMD_PWM    0xA0	/* CMD= 101x-PPPP-x PWM duty cycle */


// No operation ASM instruction. Forces a delay
#define _nop() do { __asm__ __volatile__ ("nop"); } while (0)

class MatrixDisplay
{
private:
	uint8_t *pShadowBuffers; // Will store the pixel data for each display
    uint8_t *pDisplayBuffers; // Will store the pixel data for each display
    uint8_t *pDisplayPins; // Will contain the pins for each CS
    
	// Associated pins
    uint8_t  dataPin;
    uint8_t  clkPin;
	
    uint8_t  displayCount;
    uint8_t  backBufferSize;
	
	// Converts a cartesian coordinate to a display index
	uint8_t displayXYToIndex(uint8_t x, uint8_t y);
	
	// Converts caretesian coordinate to the custom display buffer index
    uint8_t xyToIndex(uint8_t x, uint8_t y);
    
	// Enables/disables a specific display in the series
    void    selectDisplay(uint8_t displayNum);  
    void    releaseDisplay(uint8_t displayNum);
    
	// Todo combine methods using bitwise shift
	// Writes data to the write MSB first
    void    writeDataBE(int8_t bitCount, uint8_t data, bool useNop = false);
    
	// Writes data to the wire LSB first
    void    writeDataLE(int8_t bitCount, uint8_t data);
    
	// Write command to write
    void    writeCommand(uint8_t displayNum, uint8_t command);

	// High speed write to write (AtMega328 only)
    void    bitBlast(uint8_t pin, uint8_t data);
	
	// Debug, write a byte to serial
	void	dumpByte(uint8_t byte);
	
	// Debug
	void	preCommand(); // Sends 100 down the line
    	
	//TODO:
	// Write Column
	// Write Block etc
	// Take advantage of progresswrite
public:	
	// Constructor
	// Number of displays (1-4)
	// Shared clock pin
	// Shared data pin
    MatrixDisplay(uint8_t numDisplays, uint8_t clkPin, uint8_t dataPin, bool buildShadow = false);
    
	// Destructor
    ~MatrixDisplay();
    
	// Fetch a pixel from a specific one display coordinate 
    uint8_t getPixel(uint8_t displayNum, uint8_t x, uint8_t y, bool useShadow = false);
    
	// Set pixel from a specific one display coordinate
    void    setPixel(uint8_t displayNum, uint8_t x, uint8_t y, uint8_t value, bool paint = false, bool useShadow = false);

	// Initalise a display
    void    initDisplay(uint8_t displayNum, uint8_t pin, bool isMaster);
    
	// Sync display using progressive write (Can be buggy, very fast)
    void    syncDisplays();
	
	// Clear a single display. 
	// paint ? Send data to display : Only clear data
	void	clear(uint8_t displayNum, bool paint = false, bool useShadow = false);
	
	// Clear all displays
	void 	clear(bool paint = false, bool useShadow = false);
	
	// Write a single nybble to the display (the display writes 4 bits at a time min)
	void	writeNibbles(uint8_t displayNum, uint8_t addr, uint8_t* data, uint8_t nybbleCount);
	
	// Helper functions
	uint8_t getDisplayCount();
	
	// Defaults
	uint8_t getDisplayHeight();
	uint8_t getDisplayWidth();
	
	// Shadow 
	void	copyBuffer();
	
	// Shift the buffer Left|Right
	void	shiftLeft();
	void	shiftRight();
	
	// Set PWN brightness
	void	setBrightness(uint8_t dispNum, uint8_t pwmValue);
	
};

#endif
