#!/bin/bash
# Usage: ./zmuldivz.sh
export TSC_FREQ_HZ=2695950000
echo '"RUN", "N", "ZMULs", "ZDIVs", "REprodREeps", "REprodIMeps", "REquotREeps", "REquotIMeps", "REPRODeps", "REQUOTeps"' > zmuldivz.csv 2> zmuldivz.err
echo -n " 1, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "16, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n " 2, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "17, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n " 3, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "18, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n " 4, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "19, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n " 5, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "20, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n " 6, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "21, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n " 7, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "22, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n " 8, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "23, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n " 9, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "24, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n "10, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "25, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n "11, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "26, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n "12, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "27, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n "13, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "28, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n "14, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "29, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
echo -n "15, " >> zmuldivz0.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz0.csv 2>> zmuldivz0.err &
echo -n "30, " >> zmuldivz1.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz1.csv 2>> zmuldivz1.err &
wait
cat zmuldivz0.csv zmuldivz1.csv >> zmuldivz.csv
rm zmuldivz0.csv zmuldivz1.csv
cat zmuldivz0.err zmuldivz1.err >> zmuldivz.err
rm zmuldivz0.err zmuldivz1.err
echo -n "31, " >> zmuldivz.csv
./zmuldivz.exe 67108864 256 16 >> zmuldivz.csv 2>> zmuldivz.err
