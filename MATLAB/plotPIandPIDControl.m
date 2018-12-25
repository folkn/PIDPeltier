close all
%  P,I,D
%% 80,1,0
data = K8010; time = T8010; out  = O8010;
plotGraph
K8010S = envMean;
%% 80,2,0
data = K8020; time = T8020; out  = O8020;
plotGraph
K8020S = envMean;
%% 80,5,0
data = K8050; time = T8050; out  = O8050;
plotGraph
K8050S = envMean;
%% 80,10,0
data = K80100; time = T80100; out  = O80100;
plotGraph
K80100S = envMean;

%% Combined PI Control
figure
title('Temperature')
xlabel('Time (seconds)')
ylabel('Temperature (deg C)')
hold on
plot(T8010, K8010S,'DisplayName','Kp=80, Ki=1');
plot(T8020, K8020S, 'DisplayName','Kp=80, Ki=2');
plot(T8050, K8050S,'DisplayName','Kp=80, Ki=5');
plot(T80100, K80100S,'DisplayName','Kp=80, Ki=10'); 
line=refline(0, 50); line.DisplayName='Setpoint';
legend('location', 'best')
hold off;

%% 80,5,1
data = K8051; time = T8051; out  = O8051;
plotGraph
K8051S = envMean;
%% 80,5,2
data = K8052; time = T8052; out  = O8052;
plotGraph
K8052S = envMean;
%% 80,5,5
data = K8055; time = T8055; out  = O8055;
plotGraph
K8055S = envMean;
%% 80,5,10
data = K80510; time = T80510; out  = O80510;
plotGraph
K80510S = envMean;
%% Combined PID Control
figure
title('Temperautre')
xlabel('Time (seconds)')
ylabel('Temperature (deg C)')
hold on
plot(T8051, K8051S,'DisplayName','Kp=80, Ki=5, Kd=1');
plot(T8052, K8052S, 'DisplayName','Kp=80, Ki=5, Kd=2');
plot(T8055, K8055S,'DisplayName','Kp=80, Ki=5, Kd=5');
plot(T80510, K80510S,'DisplayName','Kp=80, Ki=5, Kd=10'); 
line=refline(0, 50); line.DisplayName='Setpoint';
legend('location', 'best')
hold off;


