data = KFinal   %temperature array
time = TFinal %time array
out  = OFinal  %output array
[envHigh, envLow] = envelope(data,16,'peak');
envMean = (envHigh+envLow)/2;
figure
subplot(3,1,[1 2]);
title('Temperature')
ylabel('Temperature (deg C)')
hold on
plot(time, envMean, 'r', 'LineWidth', 1)
plot(time, data, 'b')
refline(0, 50)
%refline(0,48) %Threshold
%refline(0,52) %Threshold
legend({'Sensor Temp','Smoothened Temp', 'Setpoint', 'Lower Threshold', 'Upper Threshold'},'Location','southeast')

subplot(3,1,3);
plot(time, out)
axis([0 max(time) -1 1])
title('Output')
xlabel('Time (seconds)')
ylabel('Duty Cycle')
legend({'Output Duty Cycle'},'Location','best')