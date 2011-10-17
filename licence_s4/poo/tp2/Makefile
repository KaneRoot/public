CC = javac
CFLAGS = -Wall -g -std=c99 
LDFLAGS = 
OPTIONS = $(CFLAGS) $(LDFLAGS)


all: $(EXEC).class

$(EXEC).class : $(EXEC).class $(AUTRES)
	$(CC) $@ -c $< $(OPTIONS)

%.class : %.java 
	$(CC) $< $(OPTIONS)

clean:
	@rm *.class
