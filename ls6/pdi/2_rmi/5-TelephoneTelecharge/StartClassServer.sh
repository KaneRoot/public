#!/bin/bash
if [ $# -ne 1 ] ;
then
	echo "Not enough arguments provided: require port number !"
else
	echo "Running command: 'java -Djava.security.policy=java.policy -cp ServeurDeClasse ClassFileServer $1 Sources'" ;
	java -Djava.security.policy=java.policy -cp ServeurDeClasse ClassFileServer $1 Sources
fi

