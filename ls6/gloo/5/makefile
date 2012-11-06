CC = gcc
LDFLAGS = -Wall -g
PROGNAME = pointeurs
Sources=$(shell ls *.c)
Objets=$(patsubst %.c, %.o, ${Sources})
ARCHIVE = philippe.pittoli_TP5

all : compilation

compilation : $(PROGNAME).o tri.o
	$(CC) $(LDFLAGS) -o $(PROGNAME) $(PROGNAME).o tri.o
	
%.o: %.c 
	gcc -Wall -g -c $<

clean : 
	rm *.o $(PROGNAME)

tar :
	@tar cvfz $(ARCHIVE).tar.gz *.c *.h makefile 
