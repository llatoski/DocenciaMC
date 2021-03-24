plot "e1.dsf" ev 2 w lp pt 5 t "q=2", "e10.dsf" ev 2 w lp pt 7 t "q=10"
set xlabel "E/N"
set ylabel "h(E/N)"
set xlabel font ",16"
set ylabel font ",16"
set key left
set key font ",12"
set tics font ",14"
set xtics (-3000,-2500,-2000,-1500,-1000)
set xrange [-3001:-999]
set term pngcairo enhanced
set output "histE.png"
replot
