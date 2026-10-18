#!/bin/bash
# to be run on Google Cloud
# instances (1 vCPU per core, 2 cores, 16 GB RAM):
# * c2-standard-4 Intel Cascadelake CPU @ 3.10 GHz
# * n4a-highmem-2 Google Neoverse-N3 CPU @ 3.4 GHz
./ddet.sh $1 &
./sdet.sh $1 &
wait
sync
sudo poweroff
