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

#include "SHT35.h"

void SHT35Class::init(uns8 sda, uns8 sck, uns8 rstPin) {
	
	sda_pin = sda;
	sck_pin = sck;
	rst_pin = rstPin;
	pinMode(rst_pin, OUTPUT);
	digitalWrite(rst_pin, HIGH);
	
	//Default values
	clock_stretch = CLK_STRETCH_ENABLED;
	repeat_mode = REPEAT_HIGH;
	measurement_period = MODE_MPS_05;
	
	Wire.begin();
}

void SHT35Class::send_command(uns16 cmd) {
	Wire.beginTransmission(SHT35_ADDR);
	Wire.write((cmd >> 8) & 0xFF);
	Wire.write(cmd & 0xFF);
	Wire.endTransmission();
}

void SHT35Class::read_raw() {
	uns8 raw_data[6];
	if (clock_stretch == CLK_STRETCH_ENABLED)
		while (digitalRead(sck_pin) == LOW) {yield();}
	else {
		Wire.beginTransmission(SHT35_ADDR);
		while (Wire.endTransmission() == NACK_ON_ADDR) {
			Wire.beginTransmission(SHT35_ADDR);
		}
	}
	
	Wire.requestFrom(SHT35_ADDR, 6);
	if (Wire.available()) {
		raw_data[0] = Wire.read();
		raw_data[1] = Wire.read();
		raw_data[2] = Wire.read();	//CRC
		raw_data[3] = Wire.read();
		raw_data[4] = Wire.read();
		raw_data[5] = Wire.read();	//CRC
	}
	
	raw_T = (raw_data[0] << 8) | raw_data[1];
	raw_RH = (raw_data[3] << 8) | raw_data[4];
}

void SHT35Class::enableClockStretch(uns8 en) {
	clock_stretch = en;
}

void SHT35Class::setRepeatMode(uns8 repeat) {
	repeat_mode = repeat;
}

void SHT35Class::setMeasurementPeriod(uns8 period) {
	measurement_period = period;
}

void SHT35Class::enableHeater(uns8 en) {
	if (en)
		send_command(CMD_ENABLE_HEAT);
	else
		send_command(CMD_DISABLE_HEAT);
}

void SHT35Class::softReset() {
	send_command(CMD_SOFT_RST);
}

void SHT35Class::hardReset() {
	digitalWrite(rst_pin, HIGH);
	digitalWrite(rst_pin, LOW);
	delayMicroseconds(1);
	digitalWrite(rst_pin, HIGH);
}

void SHT35Class::oneShotRead() {
	send_command(data_commands[repeat_mode + clock_stretch]);	
	read_raw();
}

uns16 SHT35Class::getSREG() {
	uns8 raw_data[3];
	
	send_command(CMD_READ_SREG);
	Wire.requestFrom(SHT35_ADDR, 3);
	
	if (Wire.available()) {
		raw_data[0] = Wire.read();
		raw_data[1] = Wire.read();
		raw_data[2] = Wire.read();	//CRC
	}
	
	sreg = (raw_data[0] << 8) | raw_data[1];
	return sreg;
}

uns8 SHT35Class::alertPending() {
	return ((sreg >> 15) & 0x01);
}

uns8 SHT35Class::heaterStatus() {
	return ((sreg >> 13) & 0x01);
}

uns8 SHT35Class::humidityTrackingAlert() {
	return ((sreg >> 11) & 0x01);
}

uns8 SHT35Class::temperatureTrackingAlert() {
	return ((sreg >> 10) & 0x01);
}

uns8 SHT35Class::resetDetected() {
	return ((sreg >> 4) & 0x01);
}

uns8 SHT35Class::lastCommandStatus() {
	return ((sreg >> 1) & 0x01);
}

uns8 SHT35Class::lastWriteChecksumStatus() {
	return (sreg & 0x01);
}

float SHT35Class::getCelsius() {
	return (raw_T / 65535.00) * 175 - 45;
}

float SHT35Class::getFahrenheit() {
	return (raw_T / 65535.00) * 315 - 49;
}

float SHT35Class::getHumidity() {
	return (raw_RH / 65535.0) * 100.0;
}

SHT35Class mod1030;