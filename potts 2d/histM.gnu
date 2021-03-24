plot "m1.dsf" t "q=2", "m10.dsf" t "q=10"
set xlabel "m"
set ylabel "h(m)"
set xlabel font ",16"
set ylabel font ",16"
set key font ",12"
set tics font ",14"
set xrange [16000:21000]
set xtics (16500,17500,18500,19500,20500)
set term pngcairo enhanced
set output "histM.png"
replot
