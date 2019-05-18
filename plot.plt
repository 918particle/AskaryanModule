set logscale 
set yrange [1.0e-10:1.0e-5]
set xrange [1.0e-3:10.0]
set pointsize 2.0
set rmargin 5
set lmargin 15
set bmargin 4
set tmargin 2
set grid
set xlabel "Frequency (GHz)" font "Courier,22"
set ylabel "RE(f)/Energy (V/MHz/TeV)" font "Courier,22" offset -4,0
set xtics font "Courier,22"
set ytics font "Courier,22"
set key font "Courier,20" nobox
set format y "10^{%+1T}"
set terminal postscript color enhanced
set output "demoplot.eps"
plot "ZHS/shower_100000000.0_1.0_ZHS.dat" w lp pt 2 lc -1 title "ZHS, 0.1 EeV, {/Symbol D}{/Symbol Q} = 1.0 deg", "RalstonBuniy/shower_100000000.0_1.0_JCAC.dat" w lp pt 6 lc -1 title "JCAC, 0.1 EeV, {/Symbol D}{/Symbol Q} = 1.0 deg"