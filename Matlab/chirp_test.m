h = animatedline;
%axis([0 1 -1 1])
tic
f0 = 1;
f1 = 10;
w0 = 2*pi*f0;
w1 = 2*pi*f1;
samples = 200; % samplerate*period
chirpFactor = ((f1-f0)/samples);
for k = 1:1000
    factor = mod(k,samples);
    w = w0+factor*chirpFactor;
    y = sin(w*toc);
    addpoints(h,k,y);
    drawnow
    pause(0.01)
end