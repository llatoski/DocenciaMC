plot "serie1.dsf" u 1:2 ev 20 w lp pt 5 t "q=2"
set xlabel "t(MCS)"
set ylabel "E(t)"
set xrange [0:500]
set xlabel font ",16"
set ylabel font ",16"
set key font ",12"
set tics font ",14"
set term pngcairo enhanced
set output "serieE.png"
replot
