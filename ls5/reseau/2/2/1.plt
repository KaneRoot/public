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

carre(x) = (sgn(sin(2*pi*x)) < 0) ? 0 : A

an(x) = A * (1 - cos(pi*x)) / (pi * x)
bn(x) = A/(pi*x) * sin(pi*x) 

f0(x) = (a0/2.) #+ an(1.) * sin(2.*pi*x) + bn(1.) * cos(2. * pi * x)
f1(x) = f0(x) + an(2.) * sin(2.* pi*x* 2) + bn(2.) * cos(2.*pi*x* 2)
f2(x) = f1(x) + an(3.) * sin(2.* pi*x* 3) + bn(3.) * cos(2.*pi*x* 3)
f3(x) = f2(x) + an(4.) * sin(2.* pi*x* 4) + bn(4.) * cos(2.*pi*x* 4)
f4(x) = f3(x) + an(5.) * sin(2.* pi*x* 5) + bn(5.) * cos(2.*pi*x* 5)

# fonction
plot carre(x), f0(x) , f1(x) , f2(x), f3(x), f4(x) lt 16
