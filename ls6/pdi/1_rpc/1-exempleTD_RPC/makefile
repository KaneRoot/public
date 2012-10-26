#----------------------------------------------
all : server client
#----------------------------------------------
server : server.c
	gcc -Wall -o server  server.c -lnsl
#----------------------------------------------
client : client.c 
	gcc -Wall -o client client.c -lrpcsvc -lnsl
#----------------------------------------------
clean :
	/bin/rm -f *.o server client *~ pok* *.ps
