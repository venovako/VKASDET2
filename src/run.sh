#!/bin/bash
# to be run on Google Cloud instances (1 vCPU per core, 2 cores):
# * c4-standard-4 Intel Xeon Platinum 6985P-C (Granite Rapids) CPU, 15 GB RAM
sudo ./no_turbo.sh
./ddet.sh $1 &
./sdet.sh $1 &
wait
./zmuldivz.sh $1
sync
sudo poweroff
