#----------------------------------------------
all : server client
#----------------------------------------------
.c.o :
	gcc -Wall -c $<
#----------------------------------------------
client : client.o xdr_matrice.o
	gcc -o client xdr_matrice.o client.o -lrpcsvc -lnsl
server : server.o xdr_matrice.o
	gcc -o server xdr_matrice.o server.o -lnsl

#----------------------------------------------
clean :
	/bin/rm -f *.o server client
