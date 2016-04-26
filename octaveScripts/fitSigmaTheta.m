%Fit sigma_theta
clear
home
close all

figure(1,'Position',[10,10,90,90]);
hold on;

minim = 1e-40;
freqs = 5.0*(1.1).^(-[0:41]);

for j=0.01:0.01:0.99
  title1 = sprintf('shower_%1.2f_lpm.dat',j);
  title2 = sprintf('shower_%1.2f_noLpm.dat',j);
  shower_lpm = load(title1);
  shower_noLpm = load(title2);
  theta = shower_lpm(:,1);
  shower_lpm(:,1) = [];
  shower_noLpm(:,1) = [];
  n = size(shower_lpm);
  n_freq = n(2);
  theta_c = 55.8;
  y = theta-theta_c;
  sigma_theta_lpm = zeros(n_freq,2);
  sigma_theta_noLpm = zeros(n_freq,2);
  ij = find(shower_lpm==0.0);
  shower_lpm(ij) = minim;
  ij = find(shower_noLpm==0.0);
  shower_noLpm(ij) = minim;
  clear ij;

  for i=1:n_freq
    E = shower_lpm(:,i)/max(shower_lpm(:,i));
    x = sqrt(-2*log(E));
    [P,S] = polyfit(x,y,1);
    sigma_theta_lpm(i,1) = -P(1);
    q = sqrt(diag(S.C)/S.df)*S.normr;
    sigma_theta_lpm(i,2) = q(1);
    
    E = shower_noLpm(:,i)/max(shower_noLpm(:,i));
    x = sqrt(-2*log(E));
    [P,S] = polyfit(x,y,1);
    sigma_theta_noLpm(i,1) = -P(1);
    q = sqrt(diag(S.C)/S.df)*S.normr;
    sigma_theta_noLpm(i,2) = q(1);
  end

  %Find sigma_theta dependence on frequency
  x = 1.0./freqs;
  x = x';
  y_lpm = sigma_theta_lpm;
  y_noLpm = sigma_theta_noLpm;
  [P_lpm,S_lpm] = polyfit(x,y_lpm(:,1),1);
  [P_noLpm,S_noLpm] = polyfit(x,y_noLpm(:,1),1);
%  he_lpm = errorbar(x,y_lpm(:,1),y_lpm(:,2),'o');
%  he_noLpm = errorbar(x,y_noLpm(:,1),y_noLpm(:,2),'o');
  he_lpm = plot(x,y_lpm(:,1),'.','markersize',20);
  he_noLpm = plot(x,y_noLpm(:,1),'.','markersize',20);
  set(he_lpm,'Color','Black');
  set(he_noLpm,'Color',[0.5 0.5 0.5]);
%  plot(x,x*P_lpm(1)+P_lpm(2),'Color','Black');
%  plot(x,x*P_noLpm(1)+P_noLpm(2),'Color',[0.5 0.5 0.5]);
end

grid on;
axis([0 10 0 4.5]);
xlabel('Freq^{-1} (GHz^{-1})','Fontname','Courier','Fontsize',20,'interpreter','tex');
ylabel('\sigma_\theta (deg)','Fontname','Courier','Fontsize',20,'interpreter','tex');
set(gca,'Fontname','Courier','Fontsize',20);
hl = legend('LPM On','LPM Off');
set(hl,'Fontname','Courier','Fontsize',18);
title('EM Showers, E_{\nu} \approx 10^{16-18} eV, RB Model','Fontname','Courier','Fontsize',18);

clear q x y theta theta_c

print -dpdf 'Oct8_plot1_all.pdf'