#!/usr/bin/gnuplot -persist

# suppression des informations non utiles
# unset title
# unset xtics
# unset ytics

# labels
set xlabel "absisses"
set ylabel "ordonnées"
set border

set sample 500
set xrange [-3:3]
set yrange [-2:2]

# fonctions sinus avec décalage de phase + changement d'amplitude
f1(x) = sin(pi*x+1)/2
f2(x) = sin(2*pi*x)

plot f1(x), f2(x), f1(x) + f2(x)
