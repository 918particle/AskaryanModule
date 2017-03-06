set logscale x
set key at 500,73 box on samplen 2 spacing 1.5 font "Courier,16" width 2
set xrange [1:1e3]
set yrange [0:180]
set format x "10^{%T}"
set rmargin 8
set lmargin 13
set tmargin 2
set bmargin 6
set xlabel "Frequency [MHz]" font "Courier,28" offset 0,-2,0
set ylabel "Phase (deg)" font "Courier,28" offset -5,0,0
set ytics scale 2 font "Courier,28"
set xtics scale 2 font "Courier,28" offset 0,-1,0
set style line 6 linecolor rgb "#000000" linewidth 5.000 dashtype 3 pointtype 2 pointsize default pointinterval 0
set style line 7 linecolor rgb "#BBBBBB" linewidth 5.000 dashtype 3 pointtype 2 pointsize default pointinterval 0
set linestyle 1 lc rgb "#000000" lw 5
set linestyle 2 lc rgb "#444444" lw 5
set linestyle 3 lc rgb "#888888" lw 5
set linestyle 4 lc rgb "#BBBBBB" lw 5
set linestyle 5 lc rgb "#DDDDDD" lw 5
set terminal postscript color enhanced
set output "March6_plot3.eps"

plot "all_phases.dat" using 1:3 w l ls 1 title "JCH and AC, F({/Symbol w}){/Symbol \271}1, {/Symbol q}={/Symbol q}_C", \
"all_phases.dat" using 1:5 w l ls 3 title "JCH and AC, F({/Symbol w}){/Symbol \271}1, {/Symbol q}-{/Symbol q}_C = -2.5{/Symbol \260}", \
"all_phases.dat" using 1:7 w l ls 4 title "JCH and AC, F({/Symbol w}){/Symbol \271}1, {/Symbol q}-{/Symbol q}_C = -5.0{/Symbol \260}", \
"all_phases.dat" using 1:9 w l ls 5 title "JCH and AC, F({/Symbol w}){/Symbol \271}1, {/Symbol q}-{/Symbol q}_C = -7.5{/Symbol \260}", \
"phase_arvz.dat" using 1:2 w l ls 7 title "arg({/Courier-Italic F}_{/Symbol w}({-d/dt RA(t,{/Symbol q}_C)})), Eq. 16 ARVZ (2011)", \
"phase_zhs.dat" using (10**$1):2 w l ls 6 title "ZHS (Fig. 16), E_{C} = 100 TeV, {/Symbol q}={/Symbol q}_C"
