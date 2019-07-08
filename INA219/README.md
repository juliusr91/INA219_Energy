# energyMeasurements
c_src contains all the arduino code. it also contains a bash script to compile the arduino code and upload it to the device.
You need avr-gcc.
you also need to clone this repo into the c_src folder https://github.com/g4lvanix/I2C-master-lib

In the i2c_master.c change the RCS frequency to 400000UL, add "#include <util/delay.h>" at the beginning of the file and add:
_delay_us(395);
to the i2c_readReg function after the second I2C_start
That way you ensure that the ADC conversion is done and the register contains a new value.

in the bash upload script you might have to change the arduino port (/dev/ttyACM0) to the right one. You can find the port using "dmesg | egrep ttyACM"

All the python things are based on Python 3.7.
the serial_read folder contains the python program for reading out the data. You will need the pyserial module.
the "viz_serial_data" contains a very small program to visualize the energy behaviour over time based on matplotlib.
