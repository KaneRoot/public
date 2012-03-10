#!/usr/bin/gnuplot -persist

# suppression des informations non utiles
#unset title
#unset xtics
#unset ytics

# labels
set title "1 et 2"
set xlabel "absisses"
set ylabel "ordonnées"

# sortie
set terminal pngcairo size 1000, 1000 enhanced font "DroidSans,12"
set output "1_2.png"

# autres options
set sample 5000
set border
set grid
set xrange [-10:10]
set yrange [-1.2:1.2]

# fonction
plot sin(x)
