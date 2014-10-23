CXX      := clang++
CXXFLAGS := --std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field -Werror -g -O0 -MMD
CXXFLAGS += $(shell pkg-config --cflags sdl2 SDL2_image SDL2_mixer SDL2_ttf glew)
LDLIBS   := $(shell pkg-config --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf glew) -lGL
SRCS     := $(wildcard *.cc)
OBJS     := $(SRCS:.cc=.o)

all: main

.PHONY: run
run: main
	./main

main: $(OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	rm -f main *.o *.d

-include *.d
