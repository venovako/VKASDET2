#!/bin/bash
gnuplot $1.gp && latexmk -pdf $1.tex && rm -fv $1.aux $1.fdb_latexmk $1.fls $1.log $1.tex $1-inc.pdf
