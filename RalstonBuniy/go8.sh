g++ createAngularLPM.cpp -o createAngularLPM Askaryan.cxx -lfftw3 -lm

./createAngularLPM 1.0e9 100MHz_LPM_F_1EeV_EM 0.1 0.1 1
./createAngularLPM 1.0e9 100MHz_LPM_noF_1EeV_EM 0.1 0.01 1
./createAngularLPM 1.0e9 250MHz_LPM_F_1EeV_EM 0.25 0.1 1
./createAngularLPM 1.0e9 250MHz_LPM_noF_1EeV_EM 0.25 0.01 1
./createAngularLPM 1.0e9 1000MHz_LPM_F_1EeV_EM 1.0 0.1 1
./createAngularLPM 1.0e9 1000MHz_LPM_noF_1EeV_EM 1.0 0.01 1

./createAngularLPM 1.0e9 100MHz_LPM_F_1EeV_Had 0.1 0.1 0
./createAngularLPM 1.0e9 100MHz_LPM_noF_1EeV_Had 0.1 0.01 0
./createAngularLPM 1.0e9 250MHz_LPM_F_1EeV_Had 0.25 0.1 0
./createAngularLPM 1.0e9 250MHz_LPM_noF_1EeV_Had 0.25 0.01 0
./createAngularLPM 1.0e9 1000MHz_LPM_F_1EeV_Had 1.0 0.1 0
./createAngularLPM 1.0e9 1000MHz_LPM_noF_1EeV_Had 1.0 0.01 0

mv shower_*.dat ~/AskaryanPapers/RecentPaperFigures
