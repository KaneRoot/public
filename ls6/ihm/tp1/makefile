CC = g++

drawtri : main.o mainframe.o
	$(CC) -o drawtri main.o mainframe.o `wx-config --libs`

main.o : main.cpp 
	$(CC) `wx-config --cxxflags` -c main.cpp -o main.o

mainframe.o : mainframe.cpp
	$(CC) `wx-config --cxxflags` -c mainframe.cpp -o mainframe.o







clean : 
	rm -f *.o drawtri 
	
