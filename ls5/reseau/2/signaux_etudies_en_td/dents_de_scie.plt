#!/usr/bin/gnuplot -persist

# labels
set xlabel "X"
set ylabel "Y"

set sample 5000
set xrange [-2:2]
set yrange [-0.3:1.3]

# autres options
set border
set grid
set terminal pngcairo size 1000, 1000 enhanced font "DroidSans,12"
set output "dent_de_scie.png"

# variables de notre simulation
A = 1.
T = 1.
f = 1./T
a0 = A

dent_de_scie(x) = x - floor(x)

a(n) = -A/(pi*n)
b(n) = 0

# généralisation de la fonction de calcul des harmoniques 
# avec une harmonique nulle (numéro y)
f(x,n) = (y == n) ? 0 : (n == 0) ? a0/2. : f(x, n - 1) + a(n) * sin(2. * pi * x * n * f) + b(n) * cos(2. * pi * x * n * f)

# L'harmonique qui doit être nulle
y = -1

# fonction
plot dent_de_scie(x), f(x,1), f(x,2), f(x,3), f(x,4) #, f(x,42) lt 7
