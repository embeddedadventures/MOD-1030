# MOD-1030 #

Arduino library and sample sketch for the <a href="http://www.embeddedadventures.com/sht35_humidity_and_temperature_sensor_mod-1030.html">SHT35 Humidity Sensor</a>.

## Using the library ##
The SHT35 Arduino library uses I2C for communication between the sensor and the Arduino. 

At the moment, the library only supports one-shot measurements. To perform a measurement, call the following functions:

    oneShotRead();
	getHumidity();
	getCelsius(); // Or getFahrenheit();

The first function performs a measurement and reads the raw measurement data from the SHT35 sensor. The following functions perform the necessary calculations to get the values in the appropriate units.

## Tested with the following boards ##
- Arduino Uno/compatible
- SAMD21-based Arduino boards

## Contact ##
Questions/comments/concerns regarding the code? Raise it up as a <a href="https://github.com/embeddedadventures/MOD-1030/issues/new">new issue</a> and we will help as soon as possible. You may also contact support@embeddedadventures.com or drances@embeddedadventures.com. Thanks!


## To Do ##
- test compatibility with ESP8266 breakout boards (ESP7 and ESP12)
- test compatibility with ESP32 breakout board
- implement periodical measurement function