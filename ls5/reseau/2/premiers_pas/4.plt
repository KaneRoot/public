#!/usr/bin/gnuplot -persist

# suppression des informations non utiles
#unset title
#unset xtics
#unset ytics

# labels
set title "4"
set xlabel "absisses"
set ylabel "ordonnées"

# sortie
set terminal pngcairo size 1000, 1000 enhanced font "DroidSans,12"
set output "4.png"

# autres options
set sample 5000
set xrange [-3:3]
set yrange [-1.2:1.2]
set border
set grid

# fonction
plot sin(2*pi*x)/2
