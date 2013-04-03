set terminal eps
set output "energy-vs-sort-algorithm.eps"

set key off
set yrange [0:3.5e+10]
set boxwidth 0.5
set style fill solid
set xlabel "Sorting Algorithms"
set ylabel "Energy Estimate (in pJoule)"
plot "./energy-vs-sort-algorithm-data" using 0:3:xtic(2) with boxes

set ylabel "Energy Estimate per Instruction (in pJoule)"
set output "energy-per-inst-vs-sort-algorithm.eps"
set yrange [6500:10000]
plot "./energy-per-inst-vs-sort-algorithm-data" using 0:3:xtic(2) with boxes

set ylabel "Energy Estimate per Instruction (in pJoule)"
set output "energy-per-inst-nomem-vs-sort-algorithm.eps"
set yrange [3200:4200]
plot "./energy-per-inst-nomem-vs-sort-algorithm-data" using 0:3:xtic(2) with boxes
