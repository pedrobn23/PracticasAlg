echo -n "" > ejecuciones.dat

for(( i=1000000; i < 100000000 ; i+=1000000 ))
do
    bin/serieUnimodal $i >> ejecuciones.dat
done
