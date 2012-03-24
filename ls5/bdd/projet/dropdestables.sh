#!/bin/bash

CREATION=creation.sql
SUPPRESSION=fichiertmp

OLDIFS=$IFS
IFS='
'
for i in $(cat ${CREATION} | grep "create table" | cut -d' ' -f 3 )
do
	echo "DROP TABLE " $i ";" >> ${SUPPRESSION}
done
IFS=${OLDIFS}
