#!/usr/bin/gnuplot -persist

# labels
set xlabel "absisses"
set ylabel "ordonnées"

# sortie
set terminal pngcairo size 1000, 1000 enhanced font "DroidSans,12"
set output "carre_4.png"

# autres options
set sample 5000
set grid
set border
set xrange [-2:2]
set yrange [-0.3:1.2]

A = 1			# notre amplitude
T = 2.			# la période
f = 1./T		# la fréquence
a0 = A			# a0

carre(x) = (sgn( sin( pi * x ) ) < 0) ? 0 : A

a(n) = (A/(pi * n)) * (1 - cos(pi * n)) 
b(n) = (A/(pi * n)) * sin(pi * n) 

# généralisation de la fonction de calcul des harmoniques
# avec une harmonique nulle (numéro y)
f(x,n) = (y == n) ? 0 : (n == 0) ? a0/2. : f(x, n - 1.) + a(n) * sin(2. * pi * x * n * f) + b(n) * cos(2. * pi * x * n * f)

# L'harmonique qui doit être nulle
y = -1

# fonction
plot carre(x), f(x,1), f(x,2), f(x,3), f(x,4) lt 7 , f(x,42)
