#!/bin/bash
# Usage: ./ddet-phi.sh RUNS
echo '"RUN", "N", "ddetns", "infs", "DDETns", "INFS", "MINRELERReps", "MAXRELERReps", "ydetns", "zdetns", "ZDETns", "ZDETAns", "FAST", "ERR"' > ddet-phi.csv 2> ddet-phi.err
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> ddet-phi.csv
	./ddet.exe 1073741824 256 >> ddet-phi.csv 2>> ddet-phi.err
done
unset R
