PORT = 10000
NOM = coin
NUM = "06 06 06 06 06"

all :
	set -v
	javac *.java
	rmic AnnuaireImpl

clean : 
	rm -f *~ *.class

compilation :
	javac *.java
	rmic AnnuaireImpl

test_applet : compilation destroy
	rmiregistry $(PORT) &
	java AnnuaireImpl $(PORT) &
	appletviewer -J-Djava.security.policy=java.policy AppletClient.html 

destroy :
	-pkill rmiregistry
	-pkill java

test_global : compilation destroy
	@sleep 1
	rmiregistry $(PORT) &
	@sleep 1
	java AnnuaireImpl $(PORT) &
	@sleep 1
	java Ajoute $(NOM) $(NUM)
	@sleep 1
	@echo "Après ajout"
	java Lister
	@echo "Après suppression"
	java Supprime $(NOM)
	@sleep 1
	java Lister

