g++ createAsk.cpp -o createAsk Askaryan.cxx -lfftw3
./createAsk 1.0e5 55.8 55.8
./createAsk 1.0e5 52.9 52.9
./createAsk 1.0e5 50.8 50.8
./createAsk 1.0e5 48.3 48.3
./createAsk 1.0e5 45.8 45.8
rm ../octaveScripts/shower*.dat
mv shower*.dat ../octaveScripts
cd ../octaveScripts
octave plotSpectra.m
evince March*pdf
