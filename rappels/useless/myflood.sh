#!/bin/bash

for i in $(seq 1 2000)
do
	echo "coucou" | write $1
	sleep 1
done

