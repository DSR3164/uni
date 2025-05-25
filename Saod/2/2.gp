set termoption enhanced
set terminal png size 1920, 1080 font "Arial, 16"
set output "Second.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 1 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 1 pt 7 ps 1
set border lw 2
set grid
set key top left
set format x "%6.0f"
plot "bres2" using 1:2 title "Binary Search Tree" with linespoints ls 1, \
"hres2" using 1:2 title "Hash Table" with linespoints ls 2