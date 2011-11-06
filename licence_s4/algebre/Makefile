CC = gcc
CFLAGS = -Wall -g #-std=c99
LDFLAGS = 
OPTIONS = $(CFLAGS) $(LDFLAGS)
EXEC = tests
FICHIERSO = calculs_base.o base.o determinant.o inversion.o

all: calculs_base.o base.o determinant.o inversion.o $(EXEC) 

$(EXEC) : $(EXEC).o 
	$(CC) -o $@ $^ $(FICHIERSO) $(OPTIONS)

$(EXEC).o : $(EXEC).c
	$(CC) -o $@ -c $< $(OPTIONS)

%.o : %.c %.h
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm $(EXEC) 2>/dev/null
