#!/usr/bin/gnuplot -persist

# suppression des informations non utiles
# unset title
# unset xtics
# unset ytics

# labels
set title "6"
set xlabel "absisses"
set ylabel "ordonnées"

# sortie
set terminal pngcairo size 1000, 1000 enhanced font "DroidSans,12"
set output "6.png"

# autres options
set sample 5000
set border
set grid
set xrange [-3:3]
set yrange [-2:2]

# fonctions sinus avec décalage de phase + changement d'amplitude
f1(x) = sin(pi*x + 1)/2 
f2(x) = sin(2*pi*x) 

plot f1(x) title "sin(pi * x + 1) / 2", f2(x) title "sin(2 * pi * x)", f1(x) + f2(x)
