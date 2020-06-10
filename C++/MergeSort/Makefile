# Written by Aaron Barge
# Copyright 2019

GCC = g++
FLAGS = -std=c++11
FLAGS += -Wall
LIBS = -pthread
LIBS += -lrt 
SIZE = 131072

sort: main.cpp stat.hpp # Compile main method
	$(GCC) $(FLAGS) -o sort $< $(LIBS)

clean: # Clean
	rm sort
