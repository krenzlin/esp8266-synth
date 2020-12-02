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
	$(ESPMAKE)

flash: build
	$(ESPMAKE) flash

run:
	$(ESPMAKE) run

help:
	$(ESPMAKE) help


TEST_SRC_FILES := $(wildcard src/*.cpp) $(wildcard tests/*.cpp)
TEST_SRC_FILES := $(filter-out src/hal.cpp, $(TEST_SRC_FILES))

bin/test: $(TEST_SRC_FILES)
	g++ -Wall -Wpedantic -g -o $@ $^ -I./include -I./src

test: bin/test
	bin/test

WRITE_SRC_FILES := write_to_file.cpp src/clock.cpp src/drums.cpp src/pattern.cpp src/osc.cpp src/misc.cpp
bin/write: $(WRITE_SRC_FILES)
	g++ -Wall -Wpedantic -g -o $@ $^ -I./include -I./src


write: bin/write
	bin/write
