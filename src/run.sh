#!/bin/bash
# to be run on Google Cloud instances (1 vCPU per core, 2 cores):
# * c2-standard-4 Intel Cascadelake CPU @ 3.10 GHz, 16 GB RAM
# * n4a-highmem-2 Google Neoverse-N3 CPU @ 3.4 GHz, 16 GB RAM
# * c4-standard-4 Intel Xeon Platinum 6985P-C (Granite Rapids) CPU, 15 GB RAM
./ddet.sh $1
./sdet.sh $1
./zmuldivz.sh $1
sync
sudo poweroff
