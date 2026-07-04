#!/bin/bash
# Usage: ./ddet.sh RUNS
echo '"RUN", "N", "ddetns", "infs", "DDETns", "INFS", "MINRELERReps", "MAXRELERReps", "NZERO", "ZDETns", "ERR"' > ddet.csv 2> ddet.err
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> ddet.csv
	./ddet.exe 67108864 256 16 >> ddet.csv 2>> ddet.err
done
unset R
