#!/bin/bash

cd Figures
./build-figures.sh
cd ..

pdflatex -shell-escape main.tex
pdflatex -shell-escape main.tex

bibtex main
pdflatex -shell-escape main.tex
pdflatex -shell-escape main.tex
