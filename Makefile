#
# Makefile for the disk emulator
# Author: D.M. Lyons
# Date: Spring 2017
#
# A List of all the source files that should be compiled together
#
SOURCES = diskprocess.cpp FCB.cpp Directory.cpp FileSystem.cpp UI_main.cpp
#
# A list of the objects that result from the compilation process
#
OBJECTS = diskprocess.o FCB.o Directory.o FileSystem.o UI_main.cpp
#
# A list of include files on which theh compilation depends
#
DEFS = diskprocess.h FCB.h Directory.h FileSystem.h
#
# What flags to send to the compiler when you compile source files
#
CPPFLAGS = -g
#
# Any libraries that should be included in the linkage step of compilation
LIBFLAGS = -lm

#

FCB_main: $(SOURCES) $(DEFS)
	g++ -std=c++11 $(CPPFAGS) $(SOURCES) -o fs $(LIBFLAGS)
