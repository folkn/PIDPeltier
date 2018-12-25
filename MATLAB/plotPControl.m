close all
%% P=1
data = K100; time = T100; out  = O100;
plotGraph
K100S = envMean;
%% P=5
data = K500; time = T500; out  = O500;
plotGraph
K500S = envMean;
%% P=10
data = K1000; time = T1000; out  = O1000;
plotGraph
K1000S = envMean;
%% P=20
data = K2000; time = T2000; out  = O2000;
plotGraph
K2000S = envMean;
%% P=40
data = K4000; time = T4000; out  = O4000;
plotGraph
K4000S = envMean;
%% P=80
data = K8000; time = T8000; out  = O8000;
plotGraph
K8000S = envMean;
%% P=100
data = K10000; time = T10000; out  = O10000;
plotGraph
K10000S = envMean;
%% Combined
figure
title('Temperautre')
xlabel('Time (seconds)')
ylabel('Temperature (deg C)')
hold on
plot(T100, K100S,'DisplayName','Kp=1');
plot(T500, K500S, 'DisplayName','Kp=5');
plot(T1000, K1000S,'DisplayName','Kp=10');
plot(T2000, K2000S,'DisplayName','Kp=20'); 
plot(T4000, K4000S,'DisplayName','Kp=40'); 
plot(T8000, K8000S,'DisplayName','Kp=80'); 
plot(T10000, K10000S,'DisplayName','Kp=100');
line=refline(0, 50); line.DisplayName='Setpoint';
legend('location', 'best')
hold off;