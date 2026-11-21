#!/bin/bash
# to be run on Google Cloud instances (1 vCPU per core, 2 cores):
# * n4d-standard-4, AMD EPYC 9B45, AOCC 6.0
export TSC_FREQ_HZ=2695950000
./zmuldivz.sh
./ddet.sh 31 &
./sdet.sh 31 &
wait
sync
sudo poweroff
