clear; home; close;

fontsize = 26;
fontname = 'Courier';
linewidth = 14.0;
axisVector = [30 80 1e-11 1e-5];

E0 = 1.0e5; %GeV
distance = 1000.0;
min = 1e-11;

%times distance, divided by energy in TeV
prefactor = distance/(E0/1000.0);

%Load the data in a loop
pf_all = [];
theta = [];
f = [];
fileList = dir();
N = length(fileList);
for i=1:N
  filetitle = fileList(i).name;
  if(length(filetitle) > 7 && filetitle(end-3:end)=='.dat' && filetitle(1)=='s')
    data = load(filetitle);
    pf_all = [pf_all data(:,2)];
    theta = [theta data(:,1)];
    p = find(filetitle=='_');
    q = find(filetitle=='.',1,'last');
    f = [f; str2num(filetitle(p+1:q-1))];
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
    semilogy(theta(:,i),pf_all(:,i)*prefactor,'-','Color',[(N-i)/N (N-i)/N (N-i)/N],'LineWidth',linewidth);
    E = ZHS_Efield(f(i),E0); %V/MHz
    E_zhs = moveOffCone_ZHS(f(i),E,theta(:,i),E0);
    E_zhs = E_zhs/distance*prefactor;
    semilogy(theta(:,i),E_zhs,'--','Color',[(N-i)/N (N-i)/N (N-i)/N],'LineWidth',linewidth);
end
xlabel('Frequency [MHz]');
ylabel('RE/E_{\nu}[V/MHz/TeV]');
axis(axisVector);

ht1 = text(31,3e-9,'0.25 GHz');
ht2 = text(68,3e-7,'1.0 GHz');
ht3 = text(68,5e-8,'0.50 GHz');

line([67 63],[4e-8 1e-9],'linestyle','--','linewidth',linewidth/3);
line([67 59],[2e-7 5e-9],'linestyle','--','linewidth',linewidth/3);

fn = findall(gcf,'-property','fontname');
set(fn,'fontname',fontname);
fs = findall(gcf,'-property','fontsize');
set(fs,'fontsize',fontsize);
set(gca,'fontsize',fontsize);
set(gca,'fontname',fontname);

set(ht1,'fontsize',18);
set(ht2,'fontsize',18);
set(ht3,'fontsize',18);

print -dpdf 'March10_plot1.pdf'
