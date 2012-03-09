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
set yrange [-2:2]

# fonctions
carre(x) = ((ceil(x)%2) == 0) ? 1 : -1

plot carre(x), sin(x)
