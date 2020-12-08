.PHONY: build flash run help test write

MAKE_ESP_ARDUINO = /home/konrad/src/makeEspArduino/makeEspArduino.mk
SKETCH = main.ino
LIBS = ./include
BUILD_DIR = ./build
UPLOAD_SPEED = 921600
CHIP = esp8266
BOARD = d1_mini
BUILD_EXTRA_FLAGS = -O2 -Wall -Wpedantic

ESPMAKE = make -f $(MAKE_ESP_ARDUINO) SKETCH=$(SKETCH) CUSTOM_LIBS=$(LIBS) BUILD_DIR=$(BUILD_DIR) UPLOAD_SPEED=$(UPLOAD_SPEED) CHIP=$(CHIP) BOARD=$(BOARD) BUILD_EXTRA_FLAGS=$(BUILD_EXTRA_FLAGS) EXCLUDE_DIRS=./tests

build:
	$(ESPMAKE)

flash: build
	$(ESPMAKE) flash

run:
	$(ESPMAKE) run

help:
	$(ESPMAKE) help


CPP_FLAGS=-Wall -Wpedantic -g
INCLUDES=-I./include -I./src

TEST_SRC_FILES := $(wildcard src/*.cpp) $(wildcard tests/*.cpp)
TEST_SRC_FILES := $(filter-out src/hal.cpp, $(TEST_SRC_FILES))
TEST_OBJS := $(addprefix build/, $(TEST_SRC_FILES:.cpp=.o))

bin/test: $(TEST_OBJS)
	g++ $(CPP_FLAGS) $(INCLUDES) -o $@ $^

test: bin/test
	bin/test

WRITE_SRC_FILES := write_to_file.cpp src/clock.cpp src/drums.cpp src/pattern.cpp src/osc.cpp src/misc.cpp src/dsp.cpp
WRITE_OBJS := $(addprefix build/, $(WRITE_SRC_FILES:.cpp=.o))
bin/write: $(WRITE_OBJS)
	g++ $(CPP_FLAGS) $(INCLUDES) -o $@ $^

write: bin/write
	bin/write

build/%.o : %.cpp
	@mkdir -p $(dir $@)
	g++ $(CPP_FLAGS) $(INCLUDES) -c $< -o $@
