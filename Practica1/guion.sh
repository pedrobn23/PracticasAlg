#!/bin/csh -vx
echo "" >> salida.dat
@ i = 1000
while ( $i < 100000 )
    ./ejecutable/$1 $i >> salida.dat
    @ i += 1000
end
