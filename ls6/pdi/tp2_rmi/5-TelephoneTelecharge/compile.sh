#!/bin/bash
set -v
javac *.java

cd ServeurDeClasse ;
javac *.java ; 

cd ../Sources ;
javac *.java ;
