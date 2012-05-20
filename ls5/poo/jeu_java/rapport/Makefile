all: compilation affichage

compilation:
	latex Global.tex 
	bibtex Global 
	latex Global.tex 
	latex Global.tex 
	dvipdf Global.dvi 

affichage:
	evince Global.pdf &!
