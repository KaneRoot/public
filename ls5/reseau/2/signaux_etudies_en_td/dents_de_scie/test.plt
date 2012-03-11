#!/usr/bin/gnuplot -persist

# labels
set title "dents de scie : utilisation du fichier .dat généré"
set xlabel "absisses"
set ylabel "ordonnées"

# sortie
#set terminal pngcairo size 1000, 1000 enhanced font "DroidSans,12"
#set output "fonction_dents_de_scie_programmeC.png"

set sample 5000
set xrange [-3:3]
set yrange [-1:1]

set border
set grid

# fonction
plot 'sf.dat'
