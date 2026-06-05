#!/bin/bash
# Usage: ./pvn-det.sh RUNS
echo '"RUN", "N", "GENns", "SDETns", "RELERRns", "INFS", "MINRELERReps", "MAXRELERReps", "ZDETFns", "ERR"' > pvn-det.csv
for ((R=1;R<=$1;++R))
do
	printf '%2d, ' $R >> pvn-det.csv
	./pvn-det.exe 1073741824 256 >> pvn-det.csv
done
unset R
