#!/bin/bash
set -v
javac *.java
rmic MessageImpl

\rm -rf tServeur tClient tReste
mkdir tServeur
mkdir tClient

for i in Client MessageImpl_Stub MessageImpl Message
do  cp $i.class tClient ; done

for i in Serveur MessageImpl_Stub MessageImpl Message
do  cp $i.class tServeur ; done

\rm *.class
