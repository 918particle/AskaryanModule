clear; home; close;

fontsize = 26;
fontname = 'Courier';
linewidth = 14.0;
axisVector = [1e0 1e4 1e-11 1e-5];

E0 = 1.0e5; %GeV
theta = 55.8*pi/180.0; %radians
distance = 1000.0;
min = 1e-11;

%times distance, divided by energy in TeV
prefactor = distance/(E0/1000.0);

fzhs = (1:10:30000);
E = ZHS_Efield(fzhs/1000,E0); %V/MHz

%Load the data in a loop
pf_all = [];
f = [];
theta = [];
fileList = dir();
N = length(fileList);
bit = true;
for i=1:N
  filetitle = fileList(i).name;
  if(length(filetitle) > 7 && filetitle(end-3:end)=='.dat' && filetitle(1)=='s')
    data = load(filetitle);
    pf_all = [pf_all data(:,2)];
    theta = [theta; str2num(filetitle(end-7:end-4))];
    if(bit)
		f = data(:,1);
		bit = false;
	end
    printf(filetitle);
  end
  printf("\n");
  fflush(stdout);
end

%Plotting Section
N = size(pf_all);
N = N(2);
figure(1,'Position',[1,1,150,150]);
hold on;
for i=1:N
  loglog(f*1000,pf_all(:,i)*prefactor,'-','Color',[(N-i)/N (N-i)/N (N-i)/N],'LineWidth',linewidth);
  E_zhs = moveOffCone_ZHS(fzhs/1000,E,theta(i),E0);
  E_zhs = E_zhs/distance*prefactor;
  loglog(fzhs,E_zhs,'--','Color',[(N-i)/N (N-i)/N (N-i)/N],'LineWidth',linewidth);
end
xlabel('Frequency [MHz]');
ylabel('RE/E_{\nu}[V/MHz/TeV]');
axis(axisVector);

ht1 = text(2e3,7e-9,'\theta_C');
ht2 = text(2.5e3,8e-8,'\theta_C');
ht4 = text(1.5e3,3e-10,'\theta_C-2.5^{\circ}');
ht5 = text(5e1,5e-11,' \theta_C-10.0^{\circ}');
ht6 = text(1.0e1,2e-7,'\theta_C-5.0^{\circ}');
ht7 = text(1.0e1,8e-8,'\theta_C-7.5^{\circ}');

line([6e1 3e2],[2e-7 3e-8],'linestyle','--','linewidth',linewidth/3);
line([6e1 3e2],[8e-8 1.2e-8],'linestyle','--','linewidth',linewidth/3);

fn = findall(gcf,'-property','fontname');
set(fn,'fontname',fontname);
fs = findall(gcf,'-property','fontsize');
set(fs,'fontsize',fontsize);
set(gca,'fontsize',fontsize);
set(gca,'fontname',fontname);

set(ht1,'fontsize',18);
set(ht2,'fontsize',18);
set(ht4,'fontsize',18);
set(ht5,'fontsize',18);
set(ht6,'fontsize',18);
set(ht7,'fontsize',18);

print -dpdf 'March8_plot1.pdf'
