set logscale
set pointsize 1.0
set key at 1300,6e-5 box on samplen 2 spacing 1.5 font "Courier,14" width 2
set xrange [1:1e4]
set yrange [1e-11:1e-4]
set format y "10^{%T}"
set format x "10^{%T}"
set xlabel "Frequency [MHz]" font "Courier,28" offset 0,-2,0
set ylabel "R E/E_{C} [V/MHz/TeV]" font "Courier,28" offset -8,0,0
set ytics scale 2 font "Courier,28"
set xtics scale 2 font "Courier,28" offset 0,-1,0
set bmargin 7
set tmargin 2
set lmargin 20
set rmargin 4
set style line 7 linecolor rgb "#BBBBBB"  linewidth 4.000 dashtype 2 pointtype 2 pointsize default pointinterval 0
set style line 8 linecolor rgb "#000000"  linewidth 4.000 dashtype 2 pointtype 2 pointsize default pointinterval 0
set linestyle 6 lc "#000000" lw 5
set linestyle 5 lc "#555555" lw 5
set linestyle 4 lc "#777777" lw 5
set linestyle 3 lc "#999999" lw 5
set linestyle 2 lc "#BBBBBB" lw 5
set linestyle 1 lc "#DDDDDD" lw 5
set style rect back fs empty border lt -1
f1(x) = 1.1e-7*(x/500.0)/(1+0.4*(x/500.0)**2)
f_arvz(x) = 1.1e-7*(x/948.949*2.5)/(1+(x/2929.69*2.5))**2;
set terminal postscript color enhanced
set output "Feb22_plot2d.eps"

plot "shower_1EeV_F.dat" using ($1*1000):2 w l ls 2 title "JCH and AC, E_C = 1EeV, LPM elongation", \
"shower_100PeV_F.dat" using ($1*1000):2 w l ls 3 title "JCH and AC, E_C = 100PeV, LPM elongation", \
"shower_10PeV_F.dat" using ($1*1000):2 w l ls 4 title "JCH and AC, E_C = 10PeV, LPM elongation", \
"shower_1PeV_F.dat" using ($1*1000):2 w l ls 5 title "JCH and AC, E_C = 1PeV, LPM elongation", \
"shower_100TeV_F.dat" using ($1*1000):2 w l ls 6 title "JCH and AC, E_C = 100TeV, LPM elongation", \
f1(x) w l ls 7 title "E_{0}(E_{{/Symbol n}}/TeV)({/Symbol n}/{/Symbol n_0})(1+0.4({/Symbol n}/{/Symbol n_0})^{2})^{-1} (ZHS)", \
"spectrum_ARVZ_fig3.dat" using (10**$1):(2.0*3.14159*(10**$2)/3.0e6/3.0e6) w l ls 8 title "Adapted from ARVZ (2011) ({/Symbol q} - {/Symbol q}_C = 0.3{/Symbol \260})"
