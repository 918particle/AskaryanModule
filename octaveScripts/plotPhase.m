clear; home; close;

fontsize = 26;
fontname = 'Courier';
linewidth = 10.0;
axisVector = [1e1 1e3 0 180];
offset = -12;
offset2 = 6;

%Load the data in a loop
pf_all = [];
theta = [];
fileList = dir();
N = length(fileList);
bit = true;
for i=1:N
  filetitle = fileList(N-i+1).name;
  if(length(filetitle) > 7 && filetitle(end-3:end)=='.dat' && filetitle(1)=='s')
    data = load(filetitle);
    t = data(:,1);
    theta = [theta; str2num(filetitle(end-7:end-4))];
    if(bit)
		dt = t(2)-t(1);
		fc = 1/(2*dt); %GHz
		[~,j] = max(data(:,2));
		bit = false;
	end
	data = circshift(data(:,2),[-j+offset,0]);
	data_f = fft(data);
	data_f = data_f(1:end/2);
	pf_all = [pf_all unwrap(arg(data_f))*180/pi-offset2];
    printf(filetitle);
  end
  printf("\n");
  fflush(stdout);
end

nm = size(pf_all);
f = linspace(fc/nm(1),fc,nm(1))*1000; %MHz
hold on;
N = nm(2);
for i=1:N
	p = find(pf_all(:,i)>180.0,1,'first');
	semilogx(f(1:p),pf_all(1:p,i),'-','Color',[i/N-0.1 i/N-0.1 i/N-0.1],'linewidth',linewidth);
end
zhs = load('phase_zhs.dat');
f_zhs = 10.^(zhs(:,1));
phase_zhs = zhs(:,2);
semilogx(f_zhs,phase_zhs,'linewidth',linewidth);

xlabel('Frequency [MHz]');
ylabel('Phase (deg)');
axis(axisVector);

fn = findall(gcf,'-property','fontname');
set(fn,'fontname',fontname);
fs = findall(gcf,'-property','fontsize');
set(fs,'fontsize',fontsize);
set(gca,'fontsize',fontsize);
set(gca,'fontname',fontname);

print -dpdf 'unss.pdf'
