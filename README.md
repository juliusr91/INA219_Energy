# energyMeasurements
c_src contains all the arduino code. it also contains a bash script to compile the arduino code and upload it to the device. 
You need avr-gcc. 
you also need to clone this repo into the c_src folder https://github.com/g4lvanix/I2C-master-lib
in the bash upload script you might have to change the arduino port (/dev/ttyACM0) to the right one. You can find the port using "dmesg | egrep ttyACM"

All the python things are based on Python 3.7.
the serial_read folder contains the python program for reading out the data. You will need the pyserial module. 
the "viz_serial_data" contains a very small program to visualize the energy behaviour over time based on matplotlib.
