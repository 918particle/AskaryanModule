close all; clear; home;

N = 40;  %Number of contours
M = [linspace(0,1,N); linspace(0,1,N); linspace(0,1,N)];
C = colormap(M');

load('shower_JE.dat');
figure(1)
hold on;
grid on;

times = -2.5+0.1:0.1:2.5;
K = max(max(abs(shower_JE(:,2:end))));

for i=1:160
  plot(times,shower_JE(i,2:end)/K,'color',[i/160, i/160, i/160])
end

P = colorbar;

set(gca,'fontsize',16,'fontname','Courier')
xlabel('Time (ns)', 'fontsize',20,'fontname','Courier');
ylabel('E-field (norm)', 'fontsize',20,'fontname','Courier');
caxis([54,58])
cbh = findobj( gcf(), 'tag', 'colorbar');
set(cbh,'fontname','courier','fontsize',16)
v = axis();
h = title('                                         Viewing Angle (deg)','fontname','courier','fontsize',16);
set(h,'position',[0 0 0])

print -dpdf Sept16_plot3.pdf