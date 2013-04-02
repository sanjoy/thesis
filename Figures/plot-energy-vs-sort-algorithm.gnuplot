set terminal eps
set output "energy-vs-sort-algorithm.eps"

set key off
set yrange [0:4e+10]
set boxwidth 0.5
set style fill solid
set title "Power Profile of Sorting Algorithms"
set xlabel "Sorting Algorithms"
set ylabel "Energy Estimate (in pJoule)"
plot "./energy-vs-sort-algorithm-data" using 0:3:xtic(2) with boxes
