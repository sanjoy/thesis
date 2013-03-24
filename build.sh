#!/bin/bash

bibtex main
pdflatex -shell-escape main.tex
pdflatex -shell-escape main.tex
