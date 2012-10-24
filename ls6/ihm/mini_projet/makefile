CC = g++
OPTIONS = `wx-config --libs --gl-libs` `wx-config --cxxflags`
ARCHIVE = philippe.pittoli
PROG = drawtri
VALGRIND_OPTIONS = --leak-check=full -v

all : $(PROG)

$(PROG) : dialogs.o main.o mainframe.o openglcanvas.o
	$(CC) -o $(PROG) dialogs.o main.o mainframe.o  $(OPTIONS)

main.o : main.cpp
	$(CC) $(OPTIONS) -c main.cpp -o main.o

mainframe.o : mainframe.h mainframe.cpp
	$(CC) $(OPTIONS) -c mainframe.cpp -o mainframe.o

dialogs.o : dialogs.h dialogs.cpp
	$(CC) $(OPTIONS) -c dialogs.cpp -o dialogs.o

openglcanvas.o : openglcanvas.h openglcanvas.cpp
	$(CC) $(OPTIONS) -c openglcanvas.cpp -o openglcanvas.o

archive : 
	-@tar cvfz $(ARCHIVE).tar.gz *

debug : all
	valgrind $(VALGRIND_OPTIONS) ./$(PROG) 
	
clean : 
	rm -f *.o drawtri $(ARCHIVE).tar.gz
	
