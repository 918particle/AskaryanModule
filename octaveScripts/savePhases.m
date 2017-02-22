clear; home; close;
axisVector = [1e1 1e3 -180 180];
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
  if(length(filetitle) > 7 && filetitle(end-3:end)=='.dat' && filetitle(1:6)=='shower')
    data = load(filetitle);
    t = data(:,1);
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
%S_obj = [f' pf_all];
%save 'all_phases.dat' S_obj
