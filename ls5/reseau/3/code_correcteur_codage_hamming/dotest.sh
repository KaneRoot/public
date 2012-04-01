#!/bin/bash

rm FileReceived
make clean
make
if [ $# = 0 ]
then
	nb=1
else
	nb=$1
fi

./medium ${nb} &

sleep 1
./receiver FileReceived &
sleep 1
./sender FileToSend

make clean
