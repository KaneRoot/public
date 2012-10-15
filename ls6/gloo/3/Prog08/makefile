PROG = hash
all :
	gcc -g hachage.c -o $(PROG)

debug :
	gdb ./$(PROG)
valgrind :
	valgrind --leak-check=full -v ./$(PROG)
clean :
	rm $(PROG)
