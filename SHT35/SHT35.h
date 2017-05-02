/*
Copyright (c) 2017, Embedded Adventures
All rights reserved.
Contact us at source [at] embeddedadventures.com
www.embeddedadventures.com
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
- Neither the name of Embedded Adventures nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.
*/

//	SHT35 MOD-1030 Humidity and Temperature Sensor Arduino library
//	Written originally by Embedded Adventures

#ifndef __SHT35_h
#define __SHT35_h

#include "Arduino.h"
#include "Wire.h"

#ifndef uns8
	#define uns8 uint8_t
#endif
#ifndef uns16
	#define uns16 uint16_t
#endif

#define		NACK_ON_ADDR			2


#define 	SHT35_ADDR				0x44

#define		CLK_STRETCH_ENABLED		0
#define		CLK_STRETCH_DISABLED	3

#define		MODE_MPS_05				6
#define		MODE_MPS_1				9
#define		MODE_MPS_2				12
#define		MODE_MPS_4				15
#define		MODE_MPS_10				18

#define		REPEAT_HIGH				0
#define		REPEAT_MED				1
#define		REPEAT_LOW				2

#define		CMD_BREAK			0x3093
#define		CMD_SOFT_RST		0x30A2
#define		CMD_ENABLE_HEAT		0x306D
#define		CMD_DISABLE_HEAT	0x3066	
#define		CMD_READ_SREG		0xF32D
#define		CMD_CLEAR_SREG		0x3041
#define		CMD_FETCH_DATA		0xE000


class SHT35Class {
private: 
	/*	Array of command bytes for data reading from SHT35	*/
	const uns16		data_commands[21] = {
	//	HIGH	MED		LOW
		0x2C06, 0x2C0D, 0x2C10,	//Clock Stretch
		0x2400, 0x240B, 0x2416,	//No clock stretch
		0x2032, 0x2024, 0x202F,	//0.5 meas per sec
		0x2130, 0x2126, 0x212D,	//1 meas per sec
		0x2236, 0x2220, 0x222B,	//2 meas per sec	
		0x2334, 0x2322, 0x2329,	//4 meas per sec
		0x2737, 0x2721, 0x272A	//10 meas per sec
	};
	
	uns16	raw_T;
	uns16	raw_RH;
	uns16	sreg;
	
	uns8	sck_pin;
	uns8	sda_pin;
	uns8	rst_pin;
	uns8	clock_stretch;
	uns8	measurement_period;
	uns8	repeat_mode;
	
	
	void	read_raw();
	void	send_command(uns16 cmd);

public:
	void	init(uns8 sda, uns8 sck, uns8 rstPin);
	
	/*	Offset for commands that use clock stretching	*/
	void	enableClockStretch(uns8 en);
	
	/*	Offset for commands that use a particular measurement period	*/
	void	setMeasurementPeriod(uns8 period);
	
	/*	Offset for commands that use HIGH, MED, or LOW repeatability	*/
	void	setRepeatMode(uns8 repeat);
	
	/*	Enable/disable heater on the SHT35 module	*/
	void	enableHeater(uns8 en);
	
	/*	Trigger system reset and reload calibration data	*/
	void	softReset();
	
	/*	Low pulse on the RESET pin	*/
	void	hardReset();

	/*	Triggers a one-shot read of temperature and relative humidity	*/
	void	oneShotRead();
	
	/*	Retrieves SREG data and saves to sreg	*/
	uns16	getSREG();
	
	/*	The following commands return the corresponding bit from sreg	*/
	uns8	alertPending();
	uns8	heaterStatus();
	uns8	humidityTrackingAlert();
	uns8	temperatureTrackingAlert();
	uns8	resetDetected();
	uns8	lastCommandStatus();
	uns8	lastWriteChecksumStatus();
	
	/*	Returns raw temperature data in Celsius	*/
	float	getCelsius();
	
	/*	Returns raw RH data in relative humidity (%)	*/
	float	getHumidity();
	
	/*	Returns raw temperature data in degrees Fahrenheit	*/
	float	getFahrenheit();
};

extern SHT35Class mod1030;

#endif