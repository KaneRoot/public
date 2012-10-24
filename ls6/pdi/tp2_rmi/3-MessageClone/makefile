# exécute ce qu'il faut
all : lancer_serveur

lancer_serveur : destroy
	rmiregistry &
	./construit.sh
	cd tServeur ; java Serveur

destroy :
	@-pkill rmiregistry 
	@sleep 1

clean : 
	@-rm -r *.class tServeur tClient

# je n'utilise pas detruit.sh
