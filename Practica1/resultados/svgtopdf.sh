mkdir pdfs 2> /dev/null

for i in *.svg
do
    j=`echo $i | cut -f 1 -d .`
    echo $j
    ` inkscape -D -z --file=`$i` --export-pdf=`$j.pdf` --export-latex`
done
