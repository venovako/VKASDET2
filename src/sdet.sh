#!/bin/bash
# Usage: ./sdet.sh RUNS
export TSC_FREQ_HZ=2695948000
echo '"RUN", "N", "sdets", "infs", "SDETs", "INFS", "MINRELERReps", "MAXRELERReps", "ydetfs", "zdetfs", "ZDETFs", "NZERO", "ERR"' > sdet.csv 2> sdet.err
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> sdet.csv
	./sdet.exe 67108864 256 16 >> sdet.csv 2>> sdet.err
done
unset R
