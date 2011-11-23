CC = gcc
CFLAGS = -Wall -g #-std=c99
LDFLAGS = -lpthread
OPTIONS = $(CFLAGS) $(LDFLAGS)
EXEC = tp5
EXEC2 = emetteur_skel
EXEC3 = recepteur_skel

all: $(EXEC) $(EXEC2) $(EXEC3)

$(EXEC) : $(EXEC).o 
	$(CC) -o $@ $^ $(OPTIONS)
$(EXEC3) : $(EXEC3).o 
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
	@rm $(EXEC) $(EXEC2) $(EXEC3) 2>/dev/null
