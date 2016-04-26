function [t] = causalLimit(theta,r)
    n = 1.79;
    c = 0.3;
    theta_c = acos(1/n);
    CCc = (cos(theta*pi/180.0)-cos(theta_c));
    q = (1-(CCc.^2)./(2*sin(theta*pi/180.0).^2))*n*r/c;
    t = q-n*r/c;
endfunction
