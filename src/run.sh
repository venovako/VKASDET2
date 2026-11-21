#!/bin/bash
# to be run on Google Cloud instances (1 vCPU per core, 2 cores):
# * n4d-standard-4, AMD EPYC 9B45
./ddet.sh $1 &
./sdet.sh $1 &
wait
./zmuldivz.sh $1
sync
sudo poweroff
