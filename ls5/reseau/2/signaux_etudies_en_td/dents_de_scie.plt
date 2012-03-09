#!/usr/bin/gnuplot -persist

# labels
set xlabel "absisses"
set ylabel "ordonnées"
set border

set sample 500
set xrange [-3:3]
set yrange [-2:2]

#set terminal png
#set output "monfichier.png"

# notre amplitude
A = 1
T=2
f=1/T
a0 = A

dent_de_scie(x) = x - floor(x)

a(n) = 
b(n) = -A/(pi*n)

f(x,n) = (n == 0) ? : f(x) + a(1.) * sin(2.*pi*x) + b(1.) * cos(2. * pi * x)

# fonction
plot dent_de_scie(x)
