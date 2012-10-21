# par défaut
MACHINE1 = localhost
MACHINE2 = localhost
CLASS_SERVER_PORT = 10000
RMIREGISTRY_PORT = 10001
NAME_TO_ADD = coin
NUM_TO_ADD = "06 66 66 66 66"

all :
	echo -ne "1. make compile\n2. make class_serveur\n3. (autre terminal) make serveur\n4. (autre terminal) make (client|ajoute|supprime)"

compile :
	-pkill rmiregistry
	sleep 1
	javac *.java
	javac ServeurDeClasse/*.java -cp ServeurDeClasse
	javac Sources/*.java -cp Sources
	#./compile.sh

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

ajoute :
	java Lance $(MACHINE1) $(CLASS_SERVER_PORT) Ajoute $(MACHINE2) $(RMIREGISTRY_PORT) $(NAME_TO_ADD) $(NUM_TO_ADD)

supprime :
	java Lance $(MACHINE1) $(CLASS_SERVER_PORT) Supprime $(MACHINE2) $(RMIREGISTRY_PORT) $(NAME_TO_ADD) 

clean :
	rm *.class */*.class
