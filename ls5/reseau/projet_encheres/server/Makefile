CC = gcc
LFLAGS = -g -W -Wall -Werror -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual -o
CFLAGS = -c -g -W -Wall -Werror -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual
EXEC = server-auctioneer
SRC = $(wildcard *.c)
#HEADERS = $(wildcard *.h) $(wildcard ../lib/*.h)
OBJ = $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : $(OBJ)
	@ $(CC) $(LFLAGS) $@ $^ 
%.o : %.c %.h
	@ $(CC) $(CFLAGS) $< -o $*.o

clean:
	@ rm -f $(OBJ)
mrproper: clean
	@ rm -f $(EXEC)
