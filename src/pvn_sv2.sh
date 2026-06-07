#!/bin/bash
#Usage ./pvn_sv2.sh (S|D|C|Z)
echo '"COND2G", "UORTHO1", "VORTHO1", "SVDRES1"' > $1.csv
../../libpvn/src/pvn_sv2.exe $1 1073741824 >> $1.csv
