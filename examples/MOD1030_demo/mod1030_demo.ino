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

#define RSTPIN  7

void setup() {
  Serial.begin(115200);
  Serial.println("Welcome to the MOD-1030 (SHT35) Humidity Sensor test sketch!");
  Serial.println("Embedded Adventures (www.embeddedadventures.com)\n");
  
  mod1030.init(A4, A5, RSTPIN);
  mod1030.enableClockStretch(CLK_STRETCH_ENABLED);
  translateSREG();
  delay(500);
}

void loop() {
  Serial.print("\n---------------\n");
  mod1030.oneShotRead();
  Serial.print("Celsius:\t");
  Serial.println(mod1030.getCelsius());
  Serial.print("Fahrenheit:\t");
  Serial.println(mod1030.getFahrenheit());
  Serial.print("RH%:\t\t");
  Serial.println(mod1030.getHumidity());
  Serial.print("---------------\n");
  delay(1000);
}   

void translateSREG() {
  Serial.print("\nSREG: ");
  Serial.println(mod1030.getSREG(), BIN);
  if (mod1030.alertPending())
    Serial.println("An alert is pending");
  if (mod1030.heaterStatus())
    Serial.println("Heater is ON");
  else
    Serial.println("Heater is OFF");
  if (mod1030.humidityTrackingAlert())
    Serial.println("RH alert");
  if (mod1030.temperatureTrackingAlert())
    Serial.println("Temperature alert");
  if (mod1030.resetDetected())
    Serial.println("A system reset occurred recently");
  if (mod1030.lastCommandStatus())
    Serial.println("Last command not processed");
  if (mod1030.lastWriteChecksumStatus())
    Serial.println("Last write transfer checksum failed");
}



