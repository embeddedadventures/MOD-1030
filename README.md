# MOD-1030 #

Arduino library and sample sketch for the <a href="">SHT35 Humidity Sensor</a>.

## Using the library ##
The SHT35 Arduino library uses I2C for communication between the sensor and the Arduino. 

At the moment, the library only supports one-shot measurements. To perform a measurement, call the following functions:

    oneShotRead();
	getHumidity();
	getCelsius(); // Or getFahrenheit();

The first function performs a measurement and reads the raw measurement data from the SHT35 sensor. The following functions perform the necessary calculations to get the values in the appropriate units.

## Tested with the following boards ##
- Arduino Uno/compatible


## To Do ##
- test compatibility with ESP8266 breakout boards (ESP7 and ESP12)
- test compatibility with ESP32 breakout board
- test compatibility with SAMD21 breakout board
- implement periodical measurement function