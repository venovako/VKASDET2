#!/bin/bash
# Usage: ./sdet-phi.sh RUNS
echo '"RUN", "N", "sdetns", "infs", "SDETns", "INFS", "MINRELERReps", "MAXRELERReps", "NZERO", "ZDETFns", "ERR"' > sdet-phi.csv 2> sdet-phi.err
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> sdet-phi.csv
	./sdet.exe 1073741824 256 >> sdet-phi.csv 2>> sdet-phi.err
done
unset R
