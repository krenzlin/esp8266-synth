.PHONY: build flash

MAKE_ESP_ARDUINO = /home/konrad/src/makeEspArduino/makeEspArduino.mk
SKETCH = main.ino
LIBS = libs/
BUILD_DIR = build/
UPLOAD_SPEED = 921600
CHIP = esp8266
BOARD = d1_mini


ESPMAKE = make -f $(MAKE_ESP_ARDUINO) SKETCH=$(SKETCH) CUSTOM_LIBS=$(LIBS) BUILD_DIR=$(BUILD_DIR) UPLOAD_SPEED=$(UPLOAD_SPEED) CHIP=$(CHIP) BOARD=$(BOARD)

build:
	$(ESPMAKE)

flash: build
	$(ESPMAKE) flash

help:
	$(ESPMAKE) help

test:
	g++ tests/*.cpp osc.cpp -I . -o test && test -s
