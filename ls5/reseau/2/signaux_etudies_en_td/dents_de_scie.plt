#!/usr/bin/gnuplot -persist

# labels
set xlabel "absisses"
set ylabel "ordonnées"
set border

set sample 500
set xrange [-3:3]
set yrange [-2:2]

set terminal png
set output "dent_scie_4.png"

# notre amplitude
A = 1.
T = 1.
f = 1./T
a0 = A

dent_de_scie(x) = x - floor(x)

a(n) = -A/(pi*n)
b(n) = 0

# généralisation de la fonction de calcul des harmoniques avec une harmonique nulle (numéro y)
f(x,n) = (y == n) ? 0 : (n == 0) ? a0/2. : f(x, n - 1) + a(n) * sin(2. * pi * x * n * f) + b(n) * cos(2. * pi * x * n * f)

# L'harmonique qui doit être nulle
y = 4

# fonction
plot dent_de_scie(x), f(x,1), f(x,2), f(x,3), f(x,4)
