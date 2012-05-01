#!/bin/bash

OLDIFS=$IFS
IFS='
'
for i in $(cat creation.sql | grep "CONSTRAINT" | cut -d' ' -f 1,2 )
do
	echo "ALTER TABLE _ DISABLE" $i ";"
done
IFS=${OLDIFS}
