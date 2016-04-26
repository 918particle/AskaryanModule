function Eout = moveOffCone_AVZ(f,Ein,theta,E0)
theta_c = acos(1/1.78); %Radians
nu0 = 0.5; %GHz
E_LPM = 2e15/1e9; %GeV
gamma = 0.3;
if(E0<1.0e6)
  delta_theta = 2.7*(nu0./f)*E0^(-0.03);
  delta_theta = delta_theta*pi/180.0;
else
  delta_theta = 2.7*(nu0./f).*((E_LPM)./(0.14*E0+E_LPM)).^gamma;
  delta_theta = delta_theta*pi/180.0;
end
Eout = sin(theta)/sin(theta_c)*Ein.*exp(-log(2)*(theta-theta_c).^2./(delta_theta).^2);
