set grid
set xrange [-3:2]
set yrange [-300:300]
set xlabel "Time (ns)" font "Courier,24" offset 0.0,-0.5
set ylabel "Amplitude (V/m)" font "Courier,24" offset -2.75,0.0
set xtics font "Courier,22"
set ytics font "Courier,22"
set key top left box on font "Courier,22"
set pointsize 2
set terminal postscript color enhanced
set output "July26_plot1.eps"

plot "july26_arvz_test.dat" w l lc -1 lw 4 title "ARVZ Implementation", "july26_arvz_data.dat" using ($1-2.05):2 w p pt 6 lc -1 title "ARVZ (2011) Fig. 3"
