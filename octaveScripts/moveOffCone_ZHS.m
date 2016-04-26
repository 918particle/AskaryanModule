function Eout = moveOffCone_ZHS(f,Ein,theta)
theta_c = 55.8; %Degrees
nu0 = 0.5; %GHz
delta_theta = 2.4*(nu0./f);
Eout = Ein.*exp(-0.5*(theta-theta_c).^2./(delta_theta).^2);
