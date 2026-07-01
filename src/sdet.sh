#!/bin/bash
# Usage: ./sdet.sh RUNS
echo '"RUN", "N", "sdetns", "infs", "SDETns", "INFS", "MINRELERReps", "MAXRELERReps", "NZERO", "ZDETFns", "ERR"' > sdet.csv 2> sdet.err
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> sdet.csv
	./sdet.exe 134217728 256 >> sdet.csv 2>> sdet.err
done
unset R
