#!/bin/bash
# Usage: ./ddet.sh RUNS
echo '"RUN", "N", "ddetns", "infs", "DDETns", "INFS", "MINRELERReps", "MAXRELERReps", "ZDETns", "ERR"' > ddet.csv
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> ddet.csv
	./ddet.exe 1073741824 256 >> ddet.csv
done
unset R
