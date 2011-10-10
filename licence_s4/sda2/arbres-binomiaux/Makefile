CC = gcc
CFLAGS = -Wall -g -std=c99 
LDFLAGS = 
OPTIONS = $(CFLAGS) $(LDFLAGS)
EXEC = arbinom

all: $(EXEC)

$(EXEC) : $(EXEC).o arbinom.o
	$(CC) -o $@ $^ $(OPTIONS)

$(EXEC).o : $(EXEC).c $(EXEC).h base.h
	$(CC) -o $@ -c $< $(OPTIONS)

%.o : %.c %.h
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm $(EXEC) 2>/dev/null
