set termoption enhanced
set terminal svg size 1920, 1080 font "Arial, 16"
set output "First.svg"
set style line 1 lc rgb "0xDC143C" lt 1 lw 1 pt 9 ps 0
set style line 2 lc rgb "0x6495ED" lt 1 lw 1 pt 7 ps 0
set style line 2 lc rgb "0x2A8D9C" lt 1 lw 1 pt 11 ps 0
set border lw 2
set grid
set key top left
set mxtics
set format x "%6.0f"
set format y "%.1t * 10^{%T}"
plot "opf2.txt" using 1:2 title "Best" with linespoints ls 1
