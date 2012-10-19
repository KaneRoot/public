# exécute ce qu'il faut
all :

exo1 :
	-pkill rmiregistry 
	sleep 1 # sinon rmiregistry n'a pas le temps de se faire kill
	rmiregistry &
	./construit.sh
	cd tServeur ; java Serveur

exo2 : 

clean : 
	-rm -r *.class tServeur tClient tReste
