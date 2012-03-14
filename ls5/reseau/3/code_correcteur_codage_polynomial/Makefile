CC=gcc
LFLAGS = -g -W -Wall -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual -Werror -o
CFLAGS = -c -g -W -Wall -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual -Werror
LDFLAGS_NET=

PROGS=sender receiver medium
FSAUVE=TP3Network.tgz
ifeq (coding2.c,$(wildcard coding2.c))
  PROGS+= sender2 receiver2
  FSAUVE=TP3Network_cor.tgz
endif

SOCKETS=s_medsend s_medrec sock_send sock_rec
all: $(PROGS)

sender: sending.o coding.o logic.o sockettoolbox.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

receiver: receiving.o decoding.o logic.o sockettoolbox.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

sender2: sending.o coding2.o logic.o sockettoolbox.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

receiver2: receiving.o decoding2.o logic.o sockettoolbox.o
	$(CC) -o $@ $^ $(LDFLAGS_NET)

medium : medium.o error.o sockettoolbox.o logic.o
	$(CC) -o $@ $^ $(LDFLAGS_NET) -lm

error.o: error.c error.h

.c.o:
	$(CC) $(CFLAGS) -c $<

sockclean:force
	rm -f $(SOCKETS)
clean: force
	rm -f *.o $(PROGS) $(SOCKETS) .depend .*.bak aaa
dep:force
	touch .depend
	makedepend -f .depend *.c
force:

ifeq (.depend,$(wildcard .depend))
include .depend
endif

sauve:force
	tar cvf - Makefile GNUmakefile *.c *.h | gzip > $(FSAUVE)

#gmake test with freeBSD
test:force $(PROGS) sockclean
	killall medium receiver sender || true
	./medium 1& sleep 1; ./receiver aaa& sleep 1; ./sender receiving.c
	diff aaa receiving.c
