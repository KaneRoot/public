CC = gcc
CFLAGS = -Wall -g #-std=c99
LDFLAGS = -lm
OPTIONS = $(CFLAGS) $(LDFLAGS)
EXEC = tests
FICHIERSO = ABP.o ABPO0.o

all: ABPO0.o ABP.o $(EXEC) 

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
