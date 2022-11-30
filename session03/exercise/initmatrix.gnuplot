set terminal svg size 900, 500
set output "initmatrix.svg"
set xlabel "Matrix dim A: M=N"

set ylabel "Wall time (in sec)"

set logscale x 
set logscale y 

set title font ",24"
set title "matrix initialization"
set key outside 
set pointsize 0.5
plot "initmatrix.data" using 1:3 with linepoints lt 2 lw 3 title "row-major","initmatrix.data" using 1:4 with linepoints lt 3 lw title "col-major"