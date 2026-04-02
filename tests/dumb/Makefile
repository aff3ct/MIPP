CC=gcc
#CPPFLAGS=-std=c++17 -Wall  -Wextra -Wpedantic -Wno-unused-parameter -march=rv64gv1_zve32f_zvl256b -mrvv-vector-bits=zvl -I./include
CPPFLAGS=-std=c23 -Wall  -Wextra -Wpedantic -Wno-unused-parameter -mavx2 -I../../include
RELEASE_FLAGS=-O3 -funroll-loops 
VPATH=./include

dumb :
	$(CC) $(CPPFLAGS) $(RELEASE_FLAGS) -o dumb dumb.cpp


