CC=g++
LDLIBS=-lglut -lGLEW -lGL
.PHONY: all clean
all: empty-window
clean: 
	find -maxdepth 1 -name '*.o' -exec rm {} \;
	find -maxdepth 1 -name 'empty-window' -exec rm {} \;
