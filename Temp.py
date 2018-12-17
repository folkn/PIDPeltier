import serial  # import Serial Library
import numpy  # Import numpy
import matplotlib.pyplot as plt  # import matplotlib library
from drawnow import *
from time import sleep
#import tkinter as Tk
#from tkinter.ttk import Frame

time = []
setpoint = []
temp =[]
output=[]
dataArray=[]
arduinoData = serial.Serial()

#keyboard Input
print('Press Enter without typing anything to get default values')
#Port
print('Select Port: \"3\" for com3 (default:3)')
keyIn = input()
try:
    tryvar = float(keyIn)
    arduinoData.port = 'com' + str(keyIn)
except ValueError:
    arduinoData.port = 'com3'

#Setpoint
print('Setpoint in deg C (default:50)')
keyIn = input()
try:
    tryvar = float(keyIn)
    setSP = tryvar
except ValueError:
    setSP = 50

#Kp
print('Kp (default 5)')
keyIn = input()
try:
    tryvar = float(keyIn)
    Kp = tryvar
except ValueError:
    Kp = 5
#Ki
print('Ki (default 5)')
keyIn = input()
try:
    tryvar = float(keyIn)
    Ki = tryvar
except ValueError:
    Ki = 5
#Kd
print('Kd (default 0)')
keyIn = input()
try:
    tryvar = float(keyIn)
    Kd = tryvar
except ValueError:
    Kd = 0
#Try to connect Serial
print('Connecting Serial')
try:
    arduinoData.open();
    arduinoData.close();
    arduinoData.open();
except ValueError:
    print("Port Error")
    exit()
while arduinoData.is_open == 0 :
    continue
sleep(2)
strToSend = (str(setSP) + ',' + str(Kp) + ',' + str(Ki) + ',' + str(Kd) + "\r\n").encode('ascii')
print(strToSend)
arduinoData.write(strToSend)
arduinoData.flush()
sleep(1)

plt.ion()  # Tell matplotlib you want interactive mode to plot live data
cnt = 0

fig = plt.figure()
def makeFig():  # Create a function that makes our desired plot
    #plt.ylim(80, 90)  # Set y min and max values
    plot1 = fig.add_subplot(211)
    plt.title('Temperature Control (Kp=' + str(curKp) + ',Ki=' + str(curKi) + ',Kd=' + str(curKd)+')')  # Plot the title
    plt.grid(True)  # Turn the grid on
    plt.ylabel('Temperature (deg C)')  # Set ylabels
    plt.plot(time, setpoint, 'r-', label='Setpoint')  # plot the temperature
    plt.plot(time, temp, 'b-', label='Temperature')
    plt.legend(loc='best')  # plot the legend
    plot2 = fig.add_subplot(212, sharex=plot1)
    plt.ylim(-260, 260)  # Set limits of second y axis- adjust to readings you are getting
    plt.plot(time, output, 'b-', label='PID Output')  # plot pressure data
    plt.ylabel('PWM DAC')  # label second y axis
    plt.ticklabel_format(useOffset=False)  # Force matplotlib to NOT autoscale y axis
    plt.legend(loc='best')  # plot the legend


while True:  # While loop that loops forever
    while (arduinoData.inWaiting() == 0):  # Wait here until there is data
        pass  # do nothing
    arduinoString = arduinoData.readline().decode('utf-8')  # read the line of text from the serial port
    print(arduinoString)
    dataArray = arduinoString.split(',')  # Split it into an array called dataArray

    curTime = float(dataArray[0])  # Convert first element to floating number and put in temp
    curSP = float(dataArray[1])  # Convert second element to floating number and put in P
    curTemp = float(dataArray[2])
    curOutput = float(dataArray[3])
    curKp = float(dataArray[4])
    curKi = float(dataArray[5])
    curKd = float(dataArray[6])

    time.append(curTime)  # Build our tempF array by appending temp readings
    setpoint.append(curSP)
    temp.append(curTemp)
    output.append(curOutput)



    drawnow(makeFig)  # Call drawnow to update our live graph
    plt.pause(.000001)  # Pause Briefly. Important to keep drawnow from crashing
    cnt = cnt + 1
