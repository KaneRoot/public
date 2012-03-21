#!/bin/bash

rm FileReceived
make clean
make

./medium 2 &

sleep 1
./receiver FileReceived &
sleep 1
./sender FileToSend

make clean
