function N = Greisen(x,E);
E_CRIT = 0.073; %Critical energy
ICE_RAD_LENGTH = 36.08; %g/cm^2
x = x/ICE_RAD_LENGTH;
a = 0.31/sqrt(log(E/E_CRIT));
b = x;
c = 1.5*x;
d = log((3*x)./(x+2.*log(E/E_CRIT)));
N = a*exp(b-c.*d);
endfunction