#!/bin/bash

./medium 1 &
./receiver FileReceived &
./sender FileToSend
#
#killall receiver & 2>/dev/null
#killall medium & 2>/dev/null
#killall sender & 2>/dev/null
