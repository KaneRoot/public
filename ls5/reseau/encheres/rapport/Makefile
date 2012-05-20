all: compilation affichage

compilation:
	latex Global.tex 
	bibtex Global 
	latex Global.tex 
	latex Global.tex 
	dvipdf Global.dvi 

affichage:
	evince Global.pdf &!

clean:
	@rm *.aux *.bbl *.blg *.dvi *.pdf *.toc *.idx *.log 2>/dev/null
