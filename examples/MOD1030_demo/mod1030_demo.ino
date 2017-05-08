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

// SHT35 MOD-1030 Humidity and Temperature Sensor Arduino test sketch
// Written originally by Embedded Adventures

#include <Wire.h>
#include <SHT35.h>

#ifdef ESP32
  #define SDAPIN  21
  #define SCLPIN  22
  #define RSTPIN  4
  #define SERIALCOM Serial
#elif defined(ARDUINO_SAMD_VARIANT_COMPLIANCE )
  #define SDAPIN  20
  #define SCLPIN  21
  #define RSTPIN  7
  #define SERIALCOM SerialUSB
#else
  #define SDAPIN  A4
  #define SCLPIN  A5
  #define RSTPIN  2
  #define SERIALCOM Serial
#endif

void setup() {
  SERIALCOM.begin(115200);
  while(!SERIALCOM);
  SERIALCOM.println("Hi there");
  mod1030.init(SDAPIN, SCLPIN, RSTPIN);
  mod1030.hardReset();
  delay(500);
  translateSREG();
  delay(1000);
}

void loop() {
  SERIALCOM.print("\n---------------\n");
  mod1030.oneShotRead();
  SERIALCOM.print("Celsius:\t");
  SERIALCOM.println(mod1030.getCelsius());
  SERIALCOM.print("Fahrenheit:\t");
  SERIALCOM.println(mod1030.getFahrenheit());
  SERIALCOM.print("RH%:\t\t");
  SERIALCOM.println(mod1030.getHumidity());
  SERIALCOM.print("---------------\n");
  delay(1000);
}

void translateSREG() {
  SERIALCOM.print("\nSREG: ");
  SERIALCOM.println(mod1030.getSREG(), BIN);
  if (mod1030.alertPending())
    SERIALCOM.println("An alert is pending");
  if (mod1030.heaterStatus())
    SERIALCOM.println("Heater is ON");
  else
    SERIALCOM.println("Heater is OFF");
  if (mod1030.humidityTrackingAlert())
    SERIALCOM.println("RH alert");
  if (mod1030.temperatureTrackingAlert())
    SERIALCOM.println("Temperature alert");
  if (mod1030.resetDetected())
    SERIALCOM.println("A system reset occurred recently");
  if (mod1030.lastCommandStatus())
    SERIALCOM.println("Last command not processed");
  if (mod1030.lastWriteChecksumStatus())
    SERIALCOM.println("Last write transfer checksum failed");
}


