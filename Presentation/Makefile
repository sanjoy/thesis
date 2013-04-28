.PHONY: Sanjoy-Das-Thesis.pdf

all: Sanjoy-Das-Presentation.pdf

view: Sanjoy-Das-Presentation.pdf
	zathura Sanjoy-Das-Presentation.pdf

Sanjoy-Das-Presentation.pdf: Presentation.tex
	latexmk  -pdf -recorder -latex='latex --shell-escape'       \
                                -pdflatex='pdflatex --shell-escape' \
                 -use-make Presentation.tex
	mv Presentation.pdf Sanjoy-Das-Presentation.pdf

clean:
	latexmk -C
