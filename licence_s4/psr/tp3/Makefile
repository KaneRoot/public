CC = gcc
CFLAGS = -Wall -g -std=c99
LDFLAGS = 
OPTIONS = $(CFLAGS) $(LDFLAGS)
EXO1 = tp3_exo1
EXO2 = tp3_exo2

all: $(EXO1) $(EXO2)


$(EXO1) : $(EXO1).o 
	$(CC) -o $@ $^ $(OPTIONS)
$(EXO2) : $(EXO2).o 
	$(CC) -o $@ $^ $(OPTIONS)

%.o : %.c 
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm $(EXO1) $(EXO2) 2>/dev/null
