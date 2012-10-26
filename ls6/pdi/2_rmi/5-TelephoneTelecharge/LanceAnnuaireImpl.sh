#!/bin/bash

## $1 = class server name
## $2 = class server port number
## $3 = rmiregistry port number

if [ $# -ne 3 ] ;
then
  echo "Not enough arguments provided: ./LanceAnnuaireImpl <class server name> <class server port number> <rmiregistry port number>"
else
	echo "Running command: 'java Lance $1 $2 AnnuaireImpl $3'" ;
	java Lance $1 $2 AnnuaireImpl $3
fi

