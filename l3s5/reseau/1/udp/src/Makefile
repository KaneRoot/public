CC = gcc
LFLAGS = -g -W -Wall -Werror -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual -o
CFLAGS = -c -g -W -Wall -Werror -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual
EXEC = sender-udp
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : $(OBJ)
	@ $(CC) $(LFLAGS) $@ $^ $(LDFLAGS)
%.o : %.c
	@ $(CC) $(CFLAGS) $< -o $*.o

clean:
	@ rm -f $(OBJ)
mrproper: clean
	@ rm -f $(EXEC)
