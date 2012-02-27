#!/bin/bash

make mrproper 2>/dev/null
make
#[ $? == 0 ] && valgrind --leak-check=full -v ./tests
[ $? == 0 ] && ./tests
