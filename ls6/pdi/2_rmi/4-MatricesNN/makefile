MACHINE = localhost
PORT = 10000

all : compilation

compilation :
	javac Op*.java Client.java

lancer_client : compilation
	java Client $(MACHINE) $(PORT)

lancer_serveur : destroy compilation
	rmiregistry $(PORT) &
	@sleep 1
	java OpMatriceImpl $(PORT)

destroy :
	@-pkill rmiregistry
	@sleep 1

clean :
	rm *.class
