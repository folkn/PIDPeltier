.mat files contain sample data as I was experimenting
.m files are the basic scripts to plot the transient data
(plotGraph.m is the main code, other scripts are for organization and requires plotGraph.m)

If using own data, use the following variable structures: (row arrays)
time = [...] 
temp = [...]
output = [...] %Duty Cycle from -1 to 1

Variable names in my .mat files:
<First Letter>
T... = time variables
K... = temp variables
O... = duty cycle variables
<Numbers>
KpKiKd
example   T8055 = Kp=80 Ki=5 Kd=5

I have used the mean of the envelope detector to filter the fluctuations of the outputs. You may change the filter methods if your peltier has another appropriate output.
