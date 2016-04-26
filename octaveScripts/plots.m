clear ; home ; close ;
pkg load control
pkg load signal

figure(1,'Position',[1,1,110,110])
axisVector = [-5 5 45.8 65.8];
axisVector2 = [-1.0 1.0];
N = 12;  %Number of contours
M = [linspace(0,1,N); linspace(0,1,N); linspace(0,1,N)];
C = colormap(M');
commonFs = 10.0; %GHz

%Load the data, determine f_c
loadtitle = 'shower_5.dat';
Efield = load(loadtitle);
n = size(Efield);
commonN = n(2);

%Normalize
if(max(max(Efield)) > abs(min(min(Efield))))
  Efield = Efield/max(max(Efield));
else
  Efield = Efield/abs(min(min(Efield)));
end

%Make the largest component in the center
[~,q] = max(Efield(floor(n(1)/2),:));
if(q>commonN/2)
  Efield = circshift(Efield,[0,-(q-commonN/2)]);
else
  Efield = circshift(Efield,[0,commonN/2-q]);
end

%Plots
angles = 45.8:0.1:65.8;
commonN
times = (1:commonN)/commonFs-commonN/commonFs/2.0;
t = causalLimit(angles,100);
contour(times,angles,Efield,N,'linewidth',4);
colorbar('fontname','Courier','fontsize',18);
axis(axisVector);
caxis(axisVector2);
grid on;
xlabel('Time (ns)','fontname','Courier','fontsize',18);
ylabel('Viewing Angle (deg)','fontname','Courier','fontsize',18);
title('10^{18} eV, (2\pi)^{1/2} \rho_0 = 2.5 m^{-1}, LPM, 1 km','fontname','Courier','fontsize',14);
set(gca,'fontsize',18,'fontname','Courier','linewidth',2);
             
hold on;
plot(t,angles,'--','color','Black','linewidth',10);

%Read out the graph
print '-dpdf' 'unss.pdf'

%Clean up
clear -regexp crit* axis* common* temp
clear i a b n C M N z q l
