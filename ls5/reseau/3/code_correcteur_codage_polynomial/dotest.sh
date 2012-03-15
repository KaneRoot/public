#!/bin/bash

rm FileReceived 2>/dev/null

#./medium 1 &

#sleep 1
#./receiver FileReceived &
#sleep 1
make clean
make
./sender FileToSend
