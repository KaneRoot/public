all: prog

NAME = start
SRCS = start.c
OBJS = $(SRCS:.c=.o)

CC = gcc

CCINCPATH = -I/usr/X11R6/include -I.
LDFLAGS = -L/usr/X11R6/lib -L. -lglut -lGLU -lm
CCINCPATH2 = -I/usr/include
LDFLAGS2 = -L/usr/lib -L. -lglut -lGLU -lm -lGL

prog:$(OBJS) $(SRCS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDFLAGS2) $(CCINCPATH2)

%.o: %.c
	$(CC) $(CCINCPATH) $(CCINCPATH2) $(CCOPTS) -c -o $@ $<

clean:
	rm -f *.o $(NAME) $(CURVE_OBJS) $(PATCH_OBJS) $(CURVE_NAME) $(PATCH_NAME)
