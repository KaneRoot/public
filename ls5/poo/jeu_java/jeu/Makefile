CC=javac

DOC=javadoc
DOCOPTION=-d doc -charset "utf-8"

FICHIERPRINCIPAL = test/TestMenu.java
MOD = $(wildcard */*/*.java */*.java )

all: doc jeu

jeu: clean compiler jouer

compiler: $(FICHIERPRINCIPAL)
	$(CC) $(FICHIERPRINCIPAL)

jouer: $(FICHIERPRINCIPAL)
	java "test.TestMenu"

doc: $(MOD)
	$(DOC) $(DOCOPTION) $(MOD)

clean:
	@find . -name "*.class" -exec rm \{\} \;
