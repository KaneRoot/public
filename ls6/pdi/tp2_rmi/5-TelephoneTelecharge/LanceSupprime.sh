#!/bin/bash

## $1 = class server name
## $2 = class server port number
## $3 = rmiregistry serveur name
## $4 = rmiregistry port number

if [ $# -ne 5 ] ;
then
	echo "Not enough arguments provided: ./LanceAjoute.sh <class server name> <class server port number> <RMIregistry server name> <rmiregistry port number> <name to delete>"
else
	echo "Running command: 'java Lance $1 $2 Ajoute $3 $4 $5'" ;
	java Lance $1 $2 Ajoute $3 $4 $5 
fi

