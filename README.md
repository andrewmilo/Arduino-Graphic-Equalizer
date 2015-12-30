# Arduino-Graphic-Equalizer
An Arduino based graphic equalizer that reacts to music.

##Description
+ My project was a graphic equalizer that reacted to sound input. Sound is input through a microphone, which is then processed by the MSGEQ7 equalizer chip into 7 distinct frequencies. Afterwards, the output is transferred into the Arduino, which uses an algorithm to map out specific frequencies to their respective columns. The amplitude of a particular frequency determines its respective height in its column.
+ The algorithm simply maps frequencies out to specific columns, scales the audio input to fit the LED matrix, lights up the LEDs in each frequency band depending on amplitude, and then refreshes the display as many times as it can per loop.

##Parts
+ Arduino UNO R3 – processes audio input controls the LED Matrix
  -	http://www.amazon.com/arduino-org-A000066-Arduino-Uno-Rev/dp/B008GRTSV6/ref=sr_1_1?s=electronics&ie=UTF8&qid=1450772558&sr=1-1&keywords=arduino+uno
+ Adafruit Electret Microphone – collects audio input
  -	https://www.adafruit.com/products/1063
+ MSGEQ7 Equalizer Chip – splits audio input into 7 distinct frequencies
  -	https://www.sparkfun.com/products/10468
+ 5V 2A Battery supply – powers the LED Matrix
  -	https://www.sparkfun.com/products/10328
+	Adafruit 16x32 LED Matrix – used as LED display
  -	https://www.adafruit.com/products/420
+	5V USB Power – charged Arduino
  -	http://www.amazon.com/Mediabridge-USB-2-0-High-Speed-Gold-Plated/dp/B001MXLD4G/ref=sr_1_2?ie=UTF8&qid=1450772718&sr=8-2&keywords=arduino+uno+cable
+	Breadboard – Held components and wires]
  -	https://www.adafruit.com/product/64
