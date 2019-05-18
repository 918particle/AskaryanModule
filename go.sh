cd RalstonBuniy
g++ createAsk.cpp Askaryan.cxx -lfftw3 -lm -o createAsk
./createAsk 1.0e8
cd ../ZHS
g++ createAsk.cpp Askaryan.cxx -lfftw3 -lm -o createAsk
./createAsk 1.0e8
cd ..

