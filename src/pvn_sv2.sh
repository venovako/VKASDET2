#!/bin/bash
#Usage ./pvn_sv2.sh (tested with openSUSE Tumbleweed's gcc-16)
echo '"T", "COND2G", "UORTHO1", "VORTHO1", "SVDRES1"' > pvn_sv2.csv
for T in S D
do
	echo -n "\"$T\"," >> pvn_sv2.csv
	../../libpvn/src/pvn_sv2.exe $T 1073741824 >> pvn_sv2.csv
done
unset T
