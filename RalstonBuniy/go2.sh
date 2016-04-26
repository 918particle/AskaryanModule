g++ createAngular.cpp -o createAngular Askaryan.cxx -lfftw3
./createAngular 1.0e5 1.0 1.0
./createAngular 1.0e5 0.5 0.5
./createAngular 1.0e5 0.25 0.25
rm ../octaveScripts/shower*.dat
mv shower*.dat ../octaveScripts
cd ../octaveScripts
octave plotAngular.m
open -a preview Mar*pdf
