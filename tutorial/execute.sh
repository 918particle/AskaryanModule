cd RalstonBuniy
g++ createAsk.cpp -o createAsk Askaryan.cxx -lfftw3 -lm
./createAsk $1
cd ../ZHS
g++ createAsk.cpp -o createAsk Askaryan.cxx -lfftw3 -lm
./createAsk $1
cd ..
gnuplot -c sample_plot.plt $1
evince July10_plot1.eps &
rm ZHS/shower*.dat
rm RalstonBuniy/shower*.dat
