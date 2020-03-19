cd RalstonBuniy
rm shower*.dat
g++ createAsk_theta.cpp Askaryan.cxx -lfftw3 -lm -o createAsk_theta
./createAsk_theta 0.75 1.0e8
cd ../ZHS
rm shower*.dat
g++ createAsk_theta.cpp Askaryan.cxx -lfftw3 -lm -o createAsk_theta
./createAsk_theta 0.75 1.0e8
cd ..