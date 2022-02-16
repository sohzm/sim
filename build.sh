#!/bin/sh

CC=g++
CFLAGS="-O3 --verbose -Wall"
SRC="main.cpp print.cpp log.cpp parsing.cpp"
INCLUDE="-lncurses"

$CC $SRC $INCLUDE -o bin/out
