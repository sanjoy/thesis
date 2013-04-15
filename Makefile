.PHONY: Sanjoy-Das-Thesis.pdf

all: Sanjoy-Das-Thesis.pdf

view: Sanjoy-Das-Thesis.pdf
	zathura Sanjoy-Das-Thesis.pdf

code:
	cd source
	make -j3

Sanjoy-Das-Thesis.pdf: main.tex
	latexmk  -pdf -recorder -latex='latex --shell-escape'       \
                                -pdflatex='pdflatex --shell-escape' \
                 -use-make main.tex
	mv main.pdf Sanjoy-Das-Thesis.pdf

clean:
	latexmk -C
