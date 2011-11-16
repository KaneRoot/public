CC = gcc
CFLAGS = -Wall -g #-std=c99
LDFLAGS = -lpthread
OPTIONS = $(CFLAGS) $(LDFLAGS)
EXEC = tp4
EXEC2 = exo3

all: $(EXEC) $(EXEC2)

$(EXEC) : $(EXEC).o 
	$(CC) -o $@ $^ $(OPTIONS)
$(EXEC2) : $(EXEC2).o 
	$(CC) -o $@ $^ $(OPTIONS)

$(EXEC).o : $(EXEC).c
	$(CC) -o $@ -c $< $(OPTIONS)

%.o : %.c 
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm $(EXEC) $(EXEC2) 2>/dev/null
