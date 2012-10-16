CC = g++
ARCHIVE = philippe.pittoli
PROG = drawtri
VALGRIND_OPTIONS = --leak-check=full -v

all : $(PROG)

$(PROG) : dialogs.o main.o mainframe.o
	$(CC) -o $(PROG) dialogs.o main.o mainframe.o `wx-config --libs`

main.o : main.cpp
	$(CC) `wx-config --cxxflags` -c main.cpp -o main.o

mainframe.o : mainframe.cpp
	$(CC) `wx-config --cxxflags` -c mainframe.cpp -o mainframe.o

dialogs.o : dialogs.cpp
	$(CC) `wx-config --cxxflags` -c dialogs.cpp -o dialogs.o

archive : 
	-@tar cvfz $(ARCHIVE).tar.gz *

debug : all
	valgrind $(VALGRIND_OPTIONS) ./$(PROG) 
	
clean : 
	rm -f *.o drawtri $(ARCHIVE).tar.gz
	
