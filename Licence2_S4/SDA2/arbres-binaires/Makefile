CC = gcc
CFLAGS = -Wall -g -std=c99 
LDFLAGS = 
OPTIONS = $(CFLAGS) $(LDFLAGS)
EXEC = abchain

all: $(EXEC)

$(EXEC) : $(EXEC).o
	$(CC) -o $@ $^ $(OPTIONS)

$(EXEC).o : $(EXEC).c $(EXEC).h
	$(CC) -o $@ -c $< $(OPTIONS)

%.o : %.c 
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm $(EXEC) 2>/dev/null
