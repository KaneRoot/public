#!/usr/bin/gnuplot -persist

# suppression des informations non utiles
#unset title
#unset xtics
#unset ytics

# labels
set xlabel "absisses"
set ylabel "ordonnées"
set border 0

set sample 5000
set xrange [-3:3]
set yrange [-1.2:1.2]

# fonction
plot sin(2*pi*x)
