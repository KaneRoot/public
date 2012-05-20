CC = gcc
OPTIONS=-lcrypt
LFLAGS = -g -W -Wall -Werror -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual -o
CFLAGS = -c -g -W -Wall -Werror -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual
EXEC = client-bidder
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : $(OBJ)
	@ $(CC) $(LFLAGS) $@ $^ $(OPTIONS)
%.o : %.c
	@ $(CC) $(CFLAGS) $< -o $*.o $(OPTIONS)

clean:
	@ rm -f $(OBJ)
mrproper: clean
	@ rm -f $(EXEC)
