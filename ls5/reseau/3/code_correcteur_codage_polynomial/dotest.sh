#!/bin/bash

rm FileReceived 2>/dev/null

./medium 1  &
./receiver FileReceived &
./sender FileToSend
