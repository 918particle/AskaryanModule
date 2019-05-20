cd RalstonBuniy
rm shower*.dat
g++ createAsk.cpp Askaryan.cxx -lfftw3 -lm -o createAsk
./createAsk 1.0e5
cd ../ZHS
rm shower*.dat
g++ createAsk.cpp Askaryan.cxx -lfftw3 -lm -o createAsk
./createAsk 1.0e5
cd ..