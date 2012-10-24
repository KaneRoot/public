## Lancer le test
Avec le makefile tout est fait automatiquement : 
	make lancer_serveur
	make lancer_client
Pour exécuter le client depuis un autre ordinateur, le plus simple est de le lancer à la main :
	java Client <serveur> <port>
Par défaut dans le makefile : localhost 10000
