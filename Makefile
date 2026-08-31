CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Iinclude $(shell pkg-config --cflags sdl2 SDL2_image SDL2_mixer)
LDLIBS := $(shell pkg-config --libs sdl2 SDL2_image SDL2_mixer)
SOURCES := $(wildcard src/*.cpp)
TARGET := game

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@ $(LDLIBS)

clean:
	rm -f $(TARGET)
