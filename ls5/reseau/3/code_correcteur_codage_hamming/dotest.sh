#!/bin/bash

./medium 1 2>/dev/null 1>&2 &
./receiver FileReceived 2>/dev/null 1>&2 &
./sender FileToSend

killall receiver & 2>/dev/null
killall medium & 2>/dev/null
killall sender & 2>/dev/null
