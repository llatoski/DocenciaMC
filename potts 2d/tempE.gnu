plot "media2.dsf" w lp pt 5 t "q=2", "media3.dsf" w lp pt 7 t "q=3", "media4.dsf" w lp pt 9 t "q=4" 
set xlabel "T"
set ylabel "E/N(T)"
set xlabel font ",16"
set ylabel font ",16"
set key font ",12"
set key bottom right
set tics font ",14"
set term pngcairo enhanced
set output "tempE.png"
replot
