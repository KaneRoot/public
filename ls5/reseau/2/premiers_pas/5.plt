#!/usr/bin/gnuplot -persist

# suppression des informations non utiles
#unset title
#unset xtics
#unset ytics

# labels
set title "5"
set xlabel "absisses"
set ylabel "ordonnées"

# sortie
set terminal pngcairo size 1000, 1000 enhanced font "DroidSans,12"
set output "5.png"

# autres options
set sample 5000
set grid
set border
set xrange [-3:3]
set yrange [-2:2]

# fonction
plot sin(2*pi*x)/2,sin(2*pi*x), sin(2*pi*x) + sin(2*pi*x)/2
