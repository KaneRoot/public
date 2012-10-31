FICHIER = assignment_3
all : compilation affichage

compilation :
	pdflatex $(FICHIER).tex

affichage :
	evince $(FICHIER).pdf

clean :
	rm $(FICHIER).log $(FICHIER).aux
distclean : clean
	rm $(FICHIER).pdf
