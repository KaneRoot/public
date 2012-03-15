CC = gcc
CFLAGS = -g -Wall

all:	testqueue
# all:	testqueue schedrr

testqueue: testqueue.o pcb.o schedrr.o
	$(CC) $(CFLAGS) -o testqueue testqueue.o pcb.o schedrr.o

schedrr: pcb.o schedrr.o simul.o
	$(CC) $(CFLAGS) -o schedrr schedrr.o pcb.o simul.o

clean:
	rm -f *.o testqueue schedrr
