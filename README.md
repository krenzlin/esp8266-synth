# Connecting the DAC via I2S


I2S needs 3 lines:

* bit clock BCK or BCLK (officially "serial clock SCK")
* word select WS or LRCLK for it selects if data is for left or right
* serial data SD (multiplexed left right data)
  * data can be in different formats I2S, Philips, left/right justified

The ESP8266 and Wemos D1 mini board are

BCK > 15 > D8
WS > 2 > D4
SD > 3 > RX(0)

This has to major impacts. Don't do anything (setMode, digitalWrite) with the LED as it is connect to pin 2.
RX0 is disabled and cannot be used to receive UART.
Together with the fact that the second UART can only transmit, you cannot receive UART data.
At least not via the hardware UARTs.
TODO Maybe software uart works


## PCM510x (purple shield)

See this excellent [stackoverflow answer](https://raspberrypi.stackexchange.com/questions/76188/how-to-make-pcm5102-dac-work-on-raspberry-pi-zerow/94951#94951)

I2S lines are labeled as:

BCK > BCK
WS > LCK
SD > DIN

Furthermore you need to connect GND to ground and VIN to 3.3 V (maybe 5V work to).
And, **important**, connect the master clock (labeled SCK but not the serial clock mentioned earlier) to ground before powering the DAC.
This signals the PCM510x that it needs to generate its own master clock.


Overview:

SCK > GND
BCK > D8
DIN > RX
LCK > D4
GND > GND
VIN > 3.3V
