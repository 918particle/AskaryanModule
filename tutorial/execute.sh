cd RalstonBuniy
g++ createAsk.cpp -o createAsk Askaryan.cxx -lfftw3 -lm
./createAsk $1
cd ../ZHS
g++ createAsk.cpp -o createAsk Askaryan.cxx -lfftw3 -lm
./createAsk $1
cd ..
gnuplot -c sample_plot.plt $1
evince July18_plot1.eps &
rm ZHS/shower*.dat
rm RalstonBuniy/shower*.dat

cd RalstonBuniy
g++ createAsk_time.cpp -o createAsk_time Askaryan.cxx -lfftw3 -lm
./createAsk_time $1
cd ../ZHS
g++ createAsk_time.cpp -o createAsk_time Askaryan.cxx -lfftw3 -lm
./createAsk_time $1
cd ..
gnuplot -c sample_plot_time.plt $1
evince July18_plot2.eps &
rm ZHS/shower*.dat
rm RalstonBuniy/shower*.dat