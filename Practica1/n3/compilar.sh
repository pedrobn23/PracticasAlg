mkdir resultados ejecutable 2> /dev/null

for i in *.cpp
do
    j=`echo $i | cut -f 1 -d .`
    g++ -O2 $i -o ../ejecutable/$j

    echo $j

    #for o in {1 .. 25}
    #do
	      echo "" > ../resultados/$j.dat
	      k="25"
	      while [ $k -le 2500 ]
	      do
	          ../ejecutable/$j $k >> ../resultados/$j.dat
	          k=$[$k+25]
	      done
	      # k=1000
	      # for ((k=1000;k<100000;k=k+1000))
	      # do
	      #     ./ejecutable/$j $k >> resultados/$j.dat
	      # done

    #done
done

