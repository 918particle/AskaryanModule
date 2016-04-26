clear ; home ; close ;
pkg load control
pkg load signal

figure(1,'Position',[1,1,2000,2000])
axisVector = [-1.5 1.5 55.8-2.0 55.8+2.0];
axisVector2 = [-1.0 1.0];
M = [0.025:0.025:1; 0.025:0.025:1; 0.025:0.025:1];
C = colormap(M');;
filterF = 5.0;
filter_order = 4;
N = 40;  %Number of contours
commonFs = 10.0; %GHz
commonN = 50; %Samples
angles = 53.8:0.025:57.8-0.025;
times = (1:commonN)/commonFs-commonN/commonFs/2.0;
tolerance = 1e-2;

%Load the data, determine f_c
Efield_ARZ = load('shower_JH.dat');
n = size(Efield_ARZ);
Efield_ARZ_final = zeros(n(1),commonN);
criticalF = Efield_ARZ(:,1);
Efield_ARZ = Efield_ARZ(:,2:end);
n = size(Efield_ARZ);

%Filter, resample, and size the data array, for Jordan-Eugene basic class
for i=1:n(1)
  [b,a] = butter(filter_order,filterF/criticalF(i),'low');
  Efield_ARZ_final(i,:) = filter(b,a,Efield_ARZ(i,:));
end

%Normalize
if(max(max(Efield_ARZ)) > abs(min(min(Efield_ARZ))))
  Efield_ARZ_final = Efield_ARZ_final/max(max(Efield_ARZ_final));
else
  Efield_ARZ_final = Efield_ARZ_final/abs(min(min(Efield_ARZ_final)));
end

%Make the largest component in the center
[~,q] = min(Efield_ARZ_final(floor(n(1)/2),:));
if(q>commonN/2)
  Efield_ARZ_final = circshift(Efield_ARZ_final,[0,-(q-commonN/2)]);
else
  Efield_ARZ_final = circshift(Efield_ARZ_final,[0,commonN/2-q]);
end

%Smooth the edges
remainder = find(abs(Efield_ARZ_final)<tolerance);
Efield_ARZ_final(remainder) = 0.0;

%Plots
contour(times,angles,abs(Efield_ARZ_final),N,'linewidth',3);
colorbar('fontname','Courier','fontsize',18);
axis(axisVector);
caxis(axisVector2);
grid on;
xlabel('Time (ns)','fontname','Courier','fontsize',18);
ylabel('Viewing Angle (deg)','fontname','Courier','fontsize',18);
set(gca,'fontsize',20,'fontname','Courier','linewidth',2);
title('|E(t)|, 1D ARZ model, Normalized')

%Clean up
clear -regexp filter* crit* axis* common* temp
clear i a b n C M N z q Efield_ARZ

%Read out the graph
print -dpdf Sept14_plot2.pdf