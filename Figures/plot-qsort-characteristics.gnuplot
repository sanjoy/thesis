set terminal eps

set yrange [0.6e+09:2e+09]
set xlabel "Size of array"
set ylabel "pJoules"

set output "qsort-energy-total.eps"

plot "./qsort-energy-data" using 1:2:(1.0) smooth bezier                       \
                  title "Energy Estimate",                                     \
     "./qsort-energy-data" with points notitle

set output "qsort-energy-per-inst.eps"

set yrange [7500:9500]
set ylabel "pJoules per instruction"

plot "< join ./qsort-energy-data ./qsort-inst-count-data" using 1:($2/$3):(1.0) \
        smooth bezier title "Energy Estimate per Instruction",  		\
     "< join ./qsort-energy-data ./qsort-inst-count-data" using 1:($2/$3) 	\
	with points notitle
