CC = gcc
CFLAGS = -Wall -g #-std=c99
LDFLAGS = 
OPTIONS = $(CFLAGS) $(LDFLAGS)
EXEC = tp3
EXEC2 = exo1

all: $(EXEC) $(EXEC2)

$(EXEC) : $(EXEC).o 
	$(CC) -o $@ $^ $(OPTIONS)

$(EXEC).o : $(EXEC).c
	$(CC) -o $@ -c $< $(OPTIONS)

%.o : %.c 
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm $(EXEC) $(EXEC2) 2>/dev/null
