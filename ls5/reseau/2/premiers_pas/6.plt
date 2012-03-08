#!/usr/bin/gnuplot -persist

# suppression des informations non utiles
# unset title
# unset xtics
# unset ytics

# labels
set xlabel "absisses"
set ylabel "ordonnées"
set border

set sample 5000
set xrange [-3:3]
set yrange [-2:2]

# fonction
plot sin(pi*x+1)/2, sin(2*pi*x), sin(2*pi*x) + sin(pi*x+1)/2
