#
#	Makefile - maintained by Philippe Pittoli - 25/09/12
#
CLI = clitcp
SRV = srvtcp
APPL = philippe.pittoli
SHELL = /bin/sh
PRINTER = philippe
COMPRESS = gzip
CC = gcc
LD = $(CC)
CFLAGS = -c -g
LDFLAGS = -g
DEFS = 

prefix = /usr/local
BINDIR = $(prefix)/bin
MANDIR = $(prefix)/man
MANEXT = 1

LIBS =
EXEC = $(CLI) $(SRV)
OBJS = common.o srvtcp.o clitcp.o
CLIOBJS = clitcp.o common.o
SRVOBJS = srvtcp.o common.o
SRCS = common.c srvtcp.c clitcp.c
INCL = common.h srvtcp.h clitcp.h

CLIMAN = $(CLI).$(MANEXT)
SRVMAN = $(SRV).$(MANEXT)
MANS = $(CLIMAN) $(SRVMAN)
SOURCES = README COPYRIGHT INSTALL Makefile $(SRCS) $(INCL) $(MANS)

#
# Règle d'inférence, construction des .o à partir des .c
#
.DEFAULT:; @echo "$< n'existe pas"
.c.o :
	$(CC) $(DEFS) $(CFLAGS) $<

# actions
all : $(EXEC)
clitcp : $(CLIOBJS)
	$(LD) $(LDFLAGS) $(CLIOBJS) $(LIBS) -o $@
srvtcp : $(SRVOBJS)
	$(LD) $(LDFLAGS) $(SRVOBJS) $(LIBS) -o $@

clean :
	-@rm $(OBJS) $(EXEC) $(APPL).tar* 1>/dev/null 2>&1
install :
	install -m 755 -o root -g staff $(EXEC) $(BINDIR)
install_man :
	install -m 644 $(MANS) $(MANDIR)/man.$(MANEXT)/
print : $(SRCS) $(INCL)
	-@$(PRINTER) $?
	-@touch $@
printall :
	-@$(PRINTER) $(SOURCES)
tar : 
	tar cvf $(APPL).tar $(SOURCES)
archive : tar
	$(COMPRESS) $(APPL).tar

# $@ : nom de la cible
# $< : nom de la première dépendance
# $^ : liste des dépendances
# $? : liste des dépendances plus récentes que la cible
# $* : nom du fichier sans suffixe
