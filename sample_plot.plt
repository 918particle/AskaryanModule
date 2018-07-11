set grid
set title "rho_0 value: 10.0 m^{-1}. Natual a-depth." font "Courier,12"
set key box on top left font "Courier,12" height 0.1 width 1.25
set xrange [1e-3:10]
set yrange [1e-11:1e-5]
set xlabel "Frequency (GHz)" font "Courier,20" offset 0,-0.75
set ylabel "R E/E_{C} (V/m/TeV)" font "Courier,20" offset -5,0
set logscale x
set logscale y
set xtics font "Courier,18"
set ytics font "Courier,18"
set format y "10^{%01T}";
set format x "10^{%01T}";
set lmargin 15
set rmargin 5
set bmargin 5
set tmargin 3
set terminal postscript color enhanced
set output "July10_plot1.eps"

plot "ZHS/shower_1000.0_0.0_zhs.dat" w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15", \
	"RalstonBuniy/shower_1000.0_0.0_JCAC.dat" w lp pt 6 lc rgb "#FF0000" title "JC and AC (2017) Fig. 5", \
#	"ZHS/shower_1000.0_-5.0_zhs.dat" w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15, -5.0 deg", \
#	"RalstonBuniy/shower_1000.0_-5.0_JCAC.dat" w lp pt 6 lc rgb "#FF0000" title "JC and AC (2017) Fig. 5, -5.0 deg", \
#	"ZHS/shower_1000.0_-2.5_zhs.dat" w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15, -2.5 deg", \
#	"RalstonBuniy/shower_1000.0_-2.5_JCAC.dat" w lp pt 6 lc rgb "#FF0000" title "JC and AC (2017) Fig. 5, -2.5 deg", \
#	"ZHS/shower_1000.0_-7.5_zhs.dat" w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15, -7.5 deg", \
#	"ZHS/shower_1000.0_-10.0_zhs.dat" w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15, -10.0 deg", \
#	"RalstonBuniy/shower_1000.0_-7.5_JCAC.dat" w lp pt 6 lc rgb "#FF0000" title "JC and AC (2017) Fig. 15, -7.5 deg", \
#	"RalstonBuniy/shower_1000.0_-10.0_JCAC.dat" w lp pt 6 lc rgb "#FF0000" title "JC and AC (2017) Fig. 15, -10.0 deg", \
