#!/bin/bash

make mrproper 2>/dev/null
make
[ $? == 0 ] && ./tests
