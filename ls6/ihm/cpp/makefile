CC = g++
ARCHIVE = philippe.pittoli
PROG = test

$(PROG) : test.o
	$(CC) -o $(PROG) test.o 

test.o : test.cpp
	$(CC) -c test.cpp -o test.o

archive : 
	-@tar cvfz $(ARCHIVE).tar.gz *

clean : 
	rm -f *.o $(PROG) $(ARCHIVE).tar.gz
