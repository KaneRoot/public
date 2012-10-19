# exécute ce qu'il faut
all :
	-pkill rmiregistry 
	sleep 1 # sinon rmiregistry n'a pas le temps de se faire kill
	rmiregistry &
	./construit.sh
	cd tServeur ; java Serveur

clean : 
	-rm -r *.class tServeur tClient tReste
# je n'utilise pas detruit.sh
