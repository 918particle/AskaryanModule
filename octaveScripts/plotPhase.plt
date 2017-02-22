set logscale x
set key at 180,77 box on samplen 2 spacing 1.5 font "Courier,16" width 2
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
set style line 6  linecolor rgb "#000000"  linewidth 4.000 dashtype 2 pointtype 2 pointsize default pointinterval 0
set style line 7  linecolor rgb "#666666"  linewidth 4.000 dashtype 2 pointtype 2 pointsize default pointinterval 0
set linestyle 1 lc rgb "#000000" lw 5
set linestyle 2 lc rgb "#333333" lw 5
set linestyle 3 lc rgb "#666666" lw 5
set linestyle 4 lc rgb "#999999" lw 5
set linestyle 5 lc rgb "#CCCCCC" lw 5
set terminal postscript color enhanced
set output "Feb22_plot1.eps"

plot "all_phases.dat" using 1:3 w l ls 1 title "JCH and AC, F({/Symbol w}){/Symbol \271}1, {/Symbol q}={/Symbol q}_C", \
"all_phases.dat" using 1:5 w l ls 2 title "JCH and AC, F({/Symbol w}){/Symbol \271}1, {/Symbol q}-{/Symbol q}_C = -2.5{/Symbol \260}", \
"all_phases.dat" using 1:7 w l ls 3 title "JCH and AC, F({/Symbol w}){/Symbol \271}1, {/Symbol q}-{/Symbol q}_C = -5.0{/Symbol \260}", \
"all_phases.dat" using 1:9 w l ls 4 title "JCH and AC, F({/Symbol w}){/Symbol \271}1, {/Symbol q}-{/Symbol q}_C = -7.5{/Symbol \260}", \
"phase_arvz.dat" using 1:2 w l ls 7 title "Eg. 16, ARVZ (2011) {/Symbol q}={/Symbol q}_C", \
"phase_zhs.dat" using (10**$1):2 w l ls 6 title "ZHS, {/Symbol q}={/Symbol q}_C"
