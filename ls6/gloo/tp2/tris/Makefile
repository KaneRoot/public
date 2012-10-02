Sources=$(shell ls *.c)
Objets=$(patsubst %.c, %.o, ${Sources})

main : ${Objets} Makefile
	gcc -g -o $@ ${Objets}

%.o: %.c 
	gcc -Wall -g -c $<

clean : 
	rm *.o main
