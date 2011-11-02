CC = gcc
CFLAGS = -Wall -g #-std=c99
LDFLAGS = 
OPTIONS = $(CFLAGS) $(LDFLAGS)
EXO = tp-note-2

all: $(EXO)

$(EXO) : $(EXO).o 
	$(CC) -o $@ $^ $(OPTIONS)

%.o : %.c 
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm $(EXO) 2>/dev/null
