# par défaut
MACHINE1 = localhost
MACHINE2 = localhost
CLASS_SERVER_PORT = 10000
RMIREGISTRY_PORT = 10001

all :

compile :
	-pkill rmiregistry
	sleep 1
	./compile.sh
	-pkill rmiregistry
	-pkill java

class_serveur :
	java -Djava.security.policy=java.policy -cp ServeurDeClasse ClassFileServer $(CLASS_SERVER_PORT) Sources
	#./StartClassServer.sh $(CLASS_SERVER_PORT)

serveur : 
	-pkill rmiregistry
	sleep 1
	rmiregistry $(RMIREGISTRY_PORT) &
	java Lance $(MACHINE1) $(CLASS_SERVER_PORT) AnnuaireImpl $(RMIREGISTRY_PORT)
	#./LanceAnnuaireImpl.sh $(CLASS) $(CLASS_SERVER_PORT) $(RMIREGISTRY_PORT)

client :
	java Lance $(MACHINE1) $(CLASS_SERVER_PORT) Client $(MACHINE2) $(RMIREGISTRY_PORT)
	#./LanceClient.sh $(MACHINE1) $(CLASS_SERVER_PORT) $(MACHINE2) $(RMIREGISTRY_PORT) 

clean :
	rm *.class */*.class
