'''Copyright (C) 2019 Julius Roeder

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
'''

import serial
import os
import struct
import time
import io

current_divider = 10
client = None

TICK_OVERFLOW = 2**16 #number of ticks before reset
NUM_TICKS = 16000000/256 #number of ticks per second
TICK_SEC = 1/NUM_TICKS

# INA Functions
def write_to_file(time_array, busvoltage_data, amp_data, power):
    with open("data1.txt","a+") as b_file:
        for line in zip(time_array[1:], busvoltage_data[1:], amp_data[1:], power[1:]):
            b_file.write(str(line)+"\n")

def get_serial_port():
    return "/dev/"+os.popen("dmesg | egrep ttyACM | cut -f3 -d: | tail -n1").read().strip()

def init_serial():
    port = serial.Serial(str(get_serial_port()), 500000, bytesize=8, parity='N', stopbits=2, timeout=None)
    time.sleep(1)
    print(port.get_settings())
    return port

def receive_data(port):
    time_array = [0]
    voltage_data = [0]
    amp_data = [0]
    power_data = [0]
    ticks = [0]
    last_time = 0
    num_lines = 0

    while(True):

        # reading uart line until \n and decoding
        line = port.readline().decode('ascii')
        line_array = line.split(",")
        if len(line_array) == 4:
            long_timer = int(line_array[0])
            short_timer = int(line_array[1])
            voltage = (int(line_array[2]) >> 3) *4 *0.001 #in V
            amp = int(line_array[3]) * 4 / 10  #times 4 because of the 0.025Ohm resistor; mV div by current divider Ohm of resistor = mA
            power = amp * voltage #in mW

            # calculating time
            if short_timer < ticks[-1]:
                tick_diff =  TICK_OVERFLOW - ticks[-1] + short_timer
            else:
                tick_diff = short_timer - ticks[-1]

            time_array.append(last_time + tick_diff*TICK_SEC)
            voltage_data.append(voltage)
            amp_data.append(amp)
            power_data.append(power)
            ticks.append(short_timer)

            num_lines += 1
            last_time = time_array[-1]
        else:
            print("too short")


        if num_lines == 100:
            print("here")
            write_to_file(time_array, voltage_data, amp_data, power_data)
            num_lines=0
            time_array = [0]
            voltage_data = [0]
            amp_data = [0]
            power_data = [0]

def send_start(port):
    # start_byte = bytearray([240])
    num_bytes = port.write(b'\x00')
    port.flush()
    if num_bytes != 1:
        print("ERROR")
    else:
        print(num_bytes)



#--------------------------------------------------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':
    port = init_serial()
    try:
        receive_data(port)
    except KeyboardInterrupt:
        print('interrupted')

    port.close()
