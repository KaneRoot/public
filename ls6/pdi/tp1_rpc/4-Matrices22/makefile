
#----------------------------------------------
all : server client 
#----------------------------------------------
server : server.o xdr_matrix.o
	gcc -o server server.o xdr_matrix.o -lnsl
#----------------------------------------------
client : client.o xdr_matrix.o
	gcc -o client client.o xdr_matrix.o -lnsl
#----------------------------------------------
clean :
	/bin/rm -f *.o server client *~ core* pok* *.ps
