set grid
set title "{/Symbol r}_{0} value: 10.0 m^{-1}, Natural a-depth" font "Courier,18"
set key box on top left font "Courier,16" height 0.1 width 1.25
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
set output "July18_plot1.eps"

file1 = sprintf("ZHS/shower_%s_0.0_zhs.dat",ARG1)
file2 = sprintf("RalstonBuniy/shower_%s_0.0_JCAC.dat",ARG1)
file3 = sprintf("ARVZ_2011/shower_%s_0.0_ARVZ.dat",ARG1)

file4 = sprintf("ZHS/shower_%s_-2.5_zhs.dat",ARG1)
file5 = sprintf("RalstonBuniy/shower_%s_-2.5_JCAC.dat",ARG1)
file6 = sprintf("ARVZ_2011/shower_%s_-2.5_ARVZ.dat",ARG1)

file7 = sprintf("ZHS/shower_%s_-5.0_zhs.dat",ARG1)
file8 = sprintf("RalstonBuniy/shower_%s_-5.0_JCAC.dat",ARG1)
file9 = sprintf("ARVZ_2011/shower_%s_-5.0_ARVZ.dat",ARG1)

file10 = sprintf("ZHS/shower_%s_-7.5_zhs.dat",ARG1)
file11 = sprintf("RalstonBuniy/shower_%s_-7.5_JCAC.dat",ARG1)
file12 = sprintf("ARVZ_2011/shower_%s_-7.5_ARVZ.dat",ARG1)

file13 = sprintf("ZHS/shower_%s_-10.0_zhs.dat",ARG1)
file14 = sprintf("RalstonBuniy/shower_%s_-10.0_JCAC.dat",ARG1)
file15 = sprintf("ARVZ_2011/shower_%s_-10.0_ARVZ.dat",ARG1)

plot file1 w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15", \
	file2 w lp pt 6 lc rgb "#FF0000" title "JCH and AC (2017) Fig. 5", \
	file3 w lp pt 6 lc rgb "#0000FF" title "ARVZ (2011) Eq. 17"

plot file4 w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15, -2.5 deg", \
	file5 w lp pt 6 lc rgb "#FF0000" title "JCH and AC (2017) Fig. 5, -2.5 deg", \
	file6 w lp pt 6 lc rgb "#0000FF" title "ARVZ (2011) Eq. 17, -2.5 deg"

plot file7 w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15, -5.0 deg", \
	file8 w lp pt 6 lc rgb "#FF0000" title "JCH and AC (2017) Fig. 5, -5.0 deg",\
	file9 w lp pt 6 lc rgb "#0000FF" title "ARVZ (2011) Eq. 17, -5.0 deg"

plot file10 w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15, -7.5 deg", \
	file11 w lp pt 6 lc rgb "#FF0000" title "JCH and AC (2017) Fig. 5, -7.5 deg",\
	file12 w lp pt 6 lc rgb "#0000FF" title "ARVZ (2011) Eq. 17, -7.5 deg"

plot file13 w lp pt 2 lc rgb "#444444" title "ZHS (1992) Fig. 15, -10.0 deg", \
	file14 w lp pt 6 lc rgb "#FF0000" title "JCH and AC (2017) Fig. 5, -10.0 deg",\
	file15 w lp pt 6 lc rgb "#0000FF" title "ARVZ (2011) Eq. 17, -10.0 deg"