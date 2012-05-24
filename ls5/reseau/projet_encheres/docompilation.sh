#!/bin/bash

# Script très basique pour recompiler l'ensemble du programme et le rapport

# si rien alors compilation, si paramètre alors "clean"
if [ $# == '0' ]
then
	$(cd server ; make mrproper ; make)
	$(cd client_bidder ; make mrproper ; make)
	$(cd client_seller ; make mrproper ; make)
	cd rapport ; make clean ; make compilation ; cd ..
else
	$(cd server ; make mrproper)
	$(cd client_bidder ; make mrproper)
	$(cd client_seller ; make mrproper)
    $(cd rapport ; make clean)
fi
