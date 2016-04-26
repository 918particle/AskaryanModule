clear; home; close;

fmax = 10; %GHz
df = 10e-3; %GHz
f = 0:df:fmax; %GHz
dt = 1/(2*fmax*1000); %us 

data1 = load('noLPM_Etheta.dat');
pf1 = abs(fft(data1)); %Volts
pf1 = pf1(1:floor(end/2)); %Positive frequencies

data2 = load('LPM_Etheta.dat');
pf2 = abs(fft(data2)); %Volts
pf2 = pf2(1:floor(end/2)); %Positive frequencies

%Plotting Section
figure(1);
grid on;
hold on;
loglog(f(1:length(pf1))*1000,pf1/max(pf1),'-','Color',[0 0 0],'LineWidth',2);
loglog(f(1:length(pf2))*1000,pf2*min(pf2)/min(pf1)*2/max(pf1),'-','Color',[0.7 0.7 0.7],'LineWidth',2);
axis([30 10000 1e-3 1e1]);
xlabel('Frequency [MHz]','fontname','Courier','fontsize',18);
ylabel('|E| (normalized)','fontname','Courier','fontsize',18);
title('1 EeV EM shower (special scaling)','fontname','Courier','fontsize',18);
hl = legend('No LPM effect','LPM effect');
set(hl,'fontname','Courier','fontsize',14);
set(gca,'fontname','Courier','fontsize',16);

print -dgif Sept18_plot2.gif