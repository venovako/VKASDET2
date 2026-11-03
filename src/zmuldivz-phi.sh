#!/bin/bash
# Usage: ./zmuldivz-phi.sh RUNS
echo '"RUN", "N", "ZMULns", "ZDIVns", "REprodREeps", "REprodIMeps", "REquotREeps", "REquotIMeps", "REPRODeps", "REQUOTeps"' > zmuldivz-phi.csv 2> zmuldivz-phi.err
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> zmuldivz-phi.csv
	./zmuldivz.exe 1073741824 256 >> zmuldivz-phi.csv 2>> zmuldivz-phi.err
done
unset R
