set terminal eps
set output "qsort-characteristics.eps"

set yrange [0.6e+09:2.4e+09]
set title "Characteristics of QuickSort"
set xlabel "Size of array"
set ylabel "pJoules"

plot "./qsort-energy-data" using 1:2:(1.0) smooth bezier                       \
                  title "Energy Estimate",                                     \
     "./qsort-energy-data" with points title "Energy Estimate",                \
     "./qsort-inst-count-normalized-data" using 1:2:(1.0) smooth bezier        \
                  title "Instructions executed (scaled)",       \
     "./qsort-inst-count-normalized-data" with points                          \
                title "Instructions executed (scaled)"

set output "qsort-characteristics-line-only.eps"

plot "./qsort-energy-data" using 1:2:(1.0) smooth bezier                       \
                  title "Energy Estimate",                                     \
     "./qsort-inst-count-normalized-data" using 1:2:(1.0) smooth bezier        \
                  title "Instructions executed (scaled)"
