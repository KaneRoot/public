Sources=$(shell ls *.c)
Objets=$(patsubst %.c, %.o, ${Sources})
ARCHIVE = philippe.pittoli_TP2

main : ${Objets} Makefile
	gcc -g -o $@ ${Objets}

%.o: %.c 
	gcc -Wall -g -c $<

clean : 
	rm *.o main
tar :
	@tar cvfz $(ARCHIVE).tar.gz *.c *.h Makefile 
