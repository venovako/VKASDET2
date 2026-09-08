#!/bin/bash
./ddet.sh $1 &
./sdet.sh $1 &
wait
sync
sudo poweroff
