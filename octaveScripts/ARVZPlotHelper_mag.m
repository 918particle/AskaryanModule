close; clear; home;fmax = 10.0; %GHzdf = 0.01; %GHzfmin = 0.001; %GHzdt = 1/(2.0*fmax); %nstmax = 1/df; %nsE_C = 1.0e2; %TeVt = -tmax/2:dt:tmax/2;f = fmin:df:fmax; %GHz[E,t] = ARZ_Efield(t,E_C);E_F = abs(fft(E));E_F = E_F(1:length(t)/2);%ScalingE_F = E_F*(dt/1000.0); %V/MHzE_F = E_F/E_C; %V/MHz/TeVf = f*1000.0; %MHzloglog(f,E_F,'-o');hold on;axis([1 1e4 1e-11 1e-5])E_ZHS = ZHS_Efield(f,E_C)/E_C;loglog(f,E_ZHS,'-o','Color','Red');