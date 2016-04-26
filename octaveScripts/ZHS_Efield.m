function [E] = ZHS_Efield(f,E0)
    norm = 1.1e-7;
    E0 = E0/1000.0; %GeV to TeV
    nu0 = 0.5; %GHz
    E = norm*E0*f/nu0.*(1+0.4*(f/nu0).^2).^(-1);