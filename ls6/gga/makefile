all: prog

NAME = start
SRCS = start.c
OBJS = $(SRCS:.c=.o)

CC = gcc

CCINCPATH = -I/usr/X11R6/include -I.
LDFLAGS = -L/usr/X11R6/lib -L. -lglut -lGLU -lm

prog:$(OBJS) $(SRCS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CCINCPATH) $(CCOPTS) -c -o $@ $<

clean:
	rm -f $(CURVE_OBJS) $(PATCH_OBJS) $(CURVE_NAME) $(PATCH_NAME)
