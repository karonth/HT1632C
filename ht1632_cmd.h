/*
	MatrixDisplay Library 2.0
	Author: Miles Burton, www.milesburton.com/
	Need a 16x24 display? Check out www.mnethardware.co.uk
	Copyright (c) 2010 Miles Burton All Rights Reserved

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
This module contains the various command codes required to control the HT1632 chip

*/

#ifndef H1632_CMD_GUARD
#define H1632_CMD_GUARD

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

#endif
