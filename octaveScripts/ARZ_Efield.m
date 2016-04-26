function [E,t] = ARZ_Efield(t,E0)
    norm = -4.5e-14*E0/1000.0; %GeV to TeV
    t_plus = t(find(t>=0));
    t_minus = t(find(t<0));
    A_plus = exp(-abs(t_plus)/.057)+(1+2.87*abs(t_plus)).^-3;
    A_minus = exp(-abs(t_minus)/.030)+(1+3.05*abs(t_minus)).^-3.5;
    A = [A_minus'; A_plus'];
    E = -diff(A)/(t(2)-t(1));
    t = t(1:end-1);
    