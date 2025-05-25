set termoption enhanced
set terminal png size 1920, 1080 font "Arial, 16"
set output "Sort2.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 2 pt 9 ps 2
set style line 2 lc rgb "0x6495ED" lt 1 lw 2 pt 7 ps 2
set style line 3 lc rgb "0x2A8D9C" lt 1 lw 2 pt 11 ps 2
set style line 4 lc rgb "0x48f015" lt 1 lw 2 pt 13 ps 2
set border lw 2
set grid
set key top left
set format x "%6.0f"
set logscale y
plot "sort" using 1:2 title "Radix Sort Time" with linespoints ls 1,\
     "sort" using 1:3 title "Odd-Even" with linespoints ls 2,\
     "sort" using 1:4 title "Merge Sort Time" with linespoints ls 3