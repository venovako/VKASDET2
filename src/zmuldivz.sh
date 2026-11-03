#!/bin/bash
# Usage: ./zmuldivz.sh RUNS
echo '"RUN", "N", "ZMULns", "ZDIVns", "REprodREeps", "REprodIMeps", "REquotREeps", "REquotIMeps", "REPRODeps", "REQUOTeps"' > zmuldivz.csv 2> zmuldivz.err
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> zmuldivz.csv
	./zmuldivz.exe 67108864 256 16 >> zmuldivz.csv 2>> zmuldivz.err
done
unset R
