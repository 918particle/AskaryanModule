function [E] = ZHS_Efield(f,E0)
    norm = 1.1e-7; %E0 should be in TeV
    nu0 = 500.0; %MHz, and f is in MHz
    E = norm*E0*f/nu0.*(1+0.4*(f/nu0).^2).^(-1);