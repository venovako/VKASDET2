#!/bin/bash
# Usage: ./ddet.sh RUNS
export TSC_FREQ_HZ=2695950000
echo '"RUN", "N", "ddets", "infs", "DDETs", "INFS", "MINRELERReps", "MAXRELERReps", "ydets", "zdets", "ZDETs", "NZERO", "ERR"' > ddet.csv 2> ddet.err
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> ddet.csv
	./ddet.exe 67108864 256 16 >> ddet.csv 2>> ddet.err
done
unset R
