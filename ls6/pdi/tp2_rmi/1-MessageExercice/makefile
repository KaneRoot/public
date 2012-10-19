
all :
	javac *.java
	rmic MessageImpl
	#	"rmiregistry port" commande à exécuter avec le port voulu
rmic_keep :
	javac *.java
	rmic -keep MessageImpl
clean :
	rm -rf *.class *~
