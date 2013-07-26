CC=g++
LDLIBS=-lglut -lGLEW -lGL
.PHONY: all clean
triangle-robust: shader_utils.o
all: triangle-robust
clean: 
	find -maxdepth 1 -name '*.o' -exec rm {} \;
	find -maxdepth 1 -name 'triangle-robust' -exec rm {} \;
