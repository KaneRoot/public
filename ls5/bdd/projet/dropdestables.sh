#!/bin/bash

OLDIFS=$IFS
IFS='
'
for i in $(cat creation.sql | grep "create table" | cut -d' ' -f 3 )
do
	echo "DROP TABLE " $i ";"
done
IFS=${OLDIFS}
