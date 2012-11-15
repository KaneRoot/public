FICHIER = hough_transform
FICHIERS = $(FICHIER).aux $(FICHIER).log $(FICHIER).out $(FICHIER).pdf

all : compilation affichage

compilation :
	pdflatex $(FICHIER).tex

#dvipdf $(FICHIER).dvi

affichage :
	evince $(FICHIER).pdf

clean :
	@-rm $(FICHIERS)
