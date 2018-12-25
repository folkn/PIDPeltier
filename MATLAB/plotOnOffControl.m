%% Combined On-Off Control
figure
title('Temperature')
xlabel('Time (seconds)')
ylabel('Temperature (deg C)')
hold on
plot(TOnOff, KOnOffS,'DisplayName','On-Off One-Directional');
plot(TOnOffBi, KOnOffBiS, 'DisplayName','On-Off bidirectional');
plot(TOnOffHyA, KOnOffHyAS,'DisplayName','On-Off Hysteresis'); 
line=refline(0, 50); line.DisplayName='Setpoint';
line2=refline(0,48); line2.DisplayName='Lower Threshold'; %Threshold
line3=refline(0,52); line3.DisplayName='Upper Threshold'; %Threshold
legend('location', 'best')
hold off;
