#!/bin/bash
#Usage ./pvn_sv2.sh
echo '"COND2G", "UORTHO1", "VORTHO1", "SVDRES1"' > Dsv2.csv
echo '"COND2G", "UORTHO1", "VORTHO1", "SVDRES1"' > Ssv2.csv
../../libpvn/src/pvn_sv2.exe D 1073741824 >> Dsv2.csv &
../../libpvn/src/pvn_sv2.exe S 1073741824 >> Ssv2.csv &
wait
sync
sudo poweroff
