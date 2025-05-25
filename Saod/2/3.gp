set termoption enhanced
set terminal png size 1920, 1080 font "Arial, 16"
set output "Sixth.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 2 pt 9 ps 2
set style line 2 lc rgb "0x6495ED" lt 1 lw 2 pt 7 ps 2
set style line 3 lc rgb "0x2A8D9C" lt 1 lw 2 pt 11 ps 2
set style line 4 lc rgb "0x48f015" lt 1 lw 2 pt 13 ps 2
set border lw 2
set grid
set key top left
set logscale y
set format x "%6.0f"
plot "hres6" using 1:2 title "Hash Table Time KP" with linespoints ls 1,\
"hres6" using 1:3 title "Hash Table Collisions KP" with linespoints ls 2,\
"hres6" using 1:4 title "Hash Table Time FNV" with linespoints ls 3,\
"hres6" using 1:5 title "Hash Table Collisions FNV" with linespoints ls 4