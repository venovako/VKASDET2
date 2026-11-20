#!/bin/bash
# Usage: ./sdet-phi.sh RUNS
export TSC_FREQ_HZ=1296996000
echo '"RUN", "N", "sdets", "infs", "SDETs", "INFS", "MINRELERReps", "MAXRELERReps", "ydetfs", "zdetfs", "ZDETFs", "NZERO", "ERR"' > sdet-phi.csv 2> sdet-phi.err
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> sdet-phi.csv
	./sdet.exe 1073741824 256 >> sdet-phi.csv 2>> sdet-phi.err
done
unset R
