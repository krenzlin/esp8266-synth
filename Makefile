.PHONY: build flash

MAKE_ESP_ARDUINO = /home/konrad/src/makeEspArduino/makeEspArduino.mk
SKETCH = main.ino
LIBS = ./include
BUILD_DIR = ./build
UPLOAD_SPEED = 921600
CHIP = esp8266
BOARD = d1_mini

ESPMAKE = make -f $(MAKE_ESP_ARDUINO) SKETCH=$(SKETCH) CUSTOM_LIBS=$(LIBS) BUILD_DIR=$(BUILD_DIR) UPLOAD_SPEED=$(UPLOAD_SPEED) CHIP=$(CHIP) BOARD=$(BOARD) EXCLUDE_DIRS=./tests

build:
	# temporarily renaming as workaround for weird missing SPI.h bug when catch is present
	mv tests/catch.hpp tests/catch.hpp.backup
	-$(ESPMAKE)
	mv tests/catch.hpp.backup tests/catch.hpp

flash: build
	mv tests/catch.hpp tests/catch.hpp.backup
	-$(ESPMAKE) flash
	mv tests/catch.hpp.backup tests/catch.hpp

help:
	$(ESPMAKE) help

test:
	g++ tests/*.cpp src/osc.cpp src/clock.cpp -I include/ -o bin/test && bin/test -s
