clear; close all;

x = load('tracks_1TeV.dat');
x = x(:,4);

b = 1:1:2000;
axisVector = [0 2e3 1 1e6];
iceDensity = 917.0;
E = 1000; %GeV
x = x*iceDensity/10;

[b,a] = hist(x,b);
figure(1,'position',[1,1,100,100]);
grid on;
hf = semilogy(a,b/4.0,'o','Color','Black');
hold on;
grid on;
semilogy(a*0.8+100,Greisen(a,E),'color','red');

%Formatting
set(gca,'Fontname','Courier','Fontsize',20');
xlabel('Depth (g/cm^2)','Fontname','Courier','Fontsize',20,'interpreter','latex');
ylabel('Total Tracks','Fontname','Courier','Fontsize',20,'interpreter','latex');
hl = legend('1 TeV','Greisen Param.');
set(hl,'Fontname','Courier','Fontsize',20);
axis(axisVector);

print -dpdf "Oct29_plot1.pdf"