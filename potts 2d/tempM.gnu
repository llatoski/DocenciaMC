plot "media2.dsf" u 1:3 t "q=2" w lp pt 5, "media3.dsf" u 1:3 t "q=3" w lp pt 7, "media4.dsf" u 1:3 w lp t "q=4" pt 9
set xlabel "T"
set ylabel "m(T)"
set xlabel font ",16"
set ylabel font ",16"
set key font ",12"
set tics font ",14"
set term pngcairo enhanced
set output "tempM.png"
replot
