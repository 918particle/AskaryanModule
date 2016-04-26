function [E] = AVZ_Efield(f,E0)
    norm = 2.53e-7;
    E0 = E0/1000.0; %GeV to TeV
    nu0 = 1.15; %GHz
    E = norm*E0*f/nu0.*(1+(f/nu0).^(1.44)).^(-1);
