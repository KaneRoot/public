
#----------------------------------------------
all : server client 
#----------------------------------------------
server : server.o xdr_matrix.o
	gcc -g -o server server.o xdr_matrix.o -lnsl
#----------------------------------------------
client : client.o xdr_matrix.o
	gcc -g -o client client.o xdr_matrix.o -lnsl
#----------------------------------------------
debug :
	valgrind --leak-check=full -v ./server
clean :
	/bin/rm -f *.o server client *~ core* pok* *.ps
