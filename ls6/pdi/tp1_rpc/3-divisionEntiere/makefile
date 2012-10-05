
#----------------------------------------------
all : server client 
#----------------------------------------------
server : server.o xdr_entiers2.o
	gcc -o server server.o xdr_entiers2.o -lnsl
#----------------------------------------------
client : client.o xdr_entiers2.o
	gcc -o client client.o xdr_entiers2.o -lnsl
#----------------------------------------------
clean :
	/bin/rm -f *.o server client *~ core* pok* *.ps
