set terminal svg size 900, 500
set output "initmatrix.svg"
set xlabel "Matrix dim A: M=N"
set title "matrix initialization"
set key outside
set pointsize 0.5
plot "initmatrix.data" using 1:3 with linespoints lt 2 lw 3 title "row-major", \
     "initmatrix.data" using 1:4 with linespoints lt 3 lw 3 title "col-major"