# Options utiles a la compilation
CFLAGS = -g -Wall

# Par defaut, on fait tout
all:	q1 q2 q3 q4 q5 q6 q7

# Edition de liens des divers programmes
q1:	q1.o e2fs.o
	cc $(CFLAGS) -o q1 q1.o e2fs.o

q2:	q2.o e2fs.o
	cc $(CFLAGS) -o q2 q2.o e2fs.o

q3:	q3.o e2fs.o
	cc $(CFLAGS) -o q3 q3.o e2fs.o

q4:	q4.o e2fs.o
	cc $(CFLAGS) -o q4 q4.o e2fs.o

q5:	q5.o e2fs.o
	cc $(CFLAGS) -o q5 q5.o e2fs.o

q6:	q6.o e2fs.o
	cc $(CFLAGS) -o q6 q6.o e2fs.o

q7:	q7.o e2fs.o
	cc $(CFLAGS) -o q7 q7.o e2fs.o

# Pour indiquer la dependance vis-a-vis de e2fs.h (en plus de q?.c qui est
# implicite)
q1.o:	e2fs.h
q2.o:	e2fs.h
q3.o:	e2fs.h
q4.o:	e2fs.h
q5.o:	e2fs.h
q6.o:	e2fs.h
q7.o:	e2fs.h
e2fs.o:	e2fs.h

# Utile pour y voir clair
clean:
	rm -f *.o q1 q2 q3 q4 q5 q6 q7
