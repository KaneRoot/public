#!/bin/bash

## $1 = class server name
## $2 = class server port number
## $3 = rmiregistry serveur name
## $4 = rmiregistry port number

if [ $# -ne 4 ] ;
then
	echo "Not enough arguments provided: ./LanceClient <class server name> <class server port number> <RMIregistry server name> <rmiregistry port number>"
else
	echo "Running command: 'java Lance $1 $2 Client $3 $4'" ;
	java Lance $1 $2 Client $3 $4
fi

