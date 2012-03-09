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
T = 2
f = 1/T
a0 = A

carre(x) = (sgn(sin(2*pi*x)) < 0) ? 0 : A

a(n) = A * (1 - cos(pi*n)) / (pi * n)
b(n) = A/(pi*n) * sin(pi*n) 

# généralisation de la fonction d'harmonique avec une harmonique nulle
f(x,n) = (y == n) ? 0 : (n > 0) ? f(x, n-1.) + a(n) * sin(2.* pi*x * n) + b(n) * cos(2. * pi * x * n) : a0/2.

# L'harmonique qui doit être nulle
y = 1

# fonction
plot carre(x), f(x,0) , f(x,1), f(x,2), f(x,3), f(x,4), f(x,5)
