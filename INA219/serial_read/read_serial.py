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
# import paramiko
import io

current_divider = 10
client = None

#--------------------------------------------------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------------------------------------------------
#Odroid Function
# def ssh_connect():
#     hostname =
#     password =
#     username =
#     client = paramiko.SSHClient()
#     client.load_system_host_keys()
#     client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
#     client.connect(hostname, username=username, password=password)
#
# def ssh_close():
#     client.close()
#
#import io
# def ssh_command(command):
#     return client.exec_command(command)

#--------------------------------------------------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------------------------------------------------


# INA Functions
def write_to_file(time_array, busvoltage_data, amp_data, power):
    with open("data1.txt","a+") as b_file:
        for line in zip(time_array, busvoltage_data, amp_data, power):
            b_file.write(str(line)+"\n")

def get_serial_port():
    return "/dev/"+os.popen("dmesg | egrep ttyACM | cut -f3 -d: | tail -n1").read().strip()

def init_serial():
    port = serial.Serial(str(get_serial_port()), 500000, bytesize=8, parity='N', stopbits=2, timeout=None)
    time.sleep(1)
    print(port.get_settings())
    return port

def receive_data(port):
    time_array = []
    busvoltage_data = []
    # shuntvoltage_data = []
    amp_data = []
    power_data = []

    num_lines = 0
    send_start(port)
    while(True):
        # time = port.read(2)
        # decoded_time = struct.unpack("<H", time)[0]


        line = port.readline()
        print(line)
        # line_array = line.split(",")
        # if len(line_array) == 3:
        #     print (int(line_array[0]))
            # print ((int(line_array[1]) >> 3) *4 *0.001) #in V)
            # print (",")
            # print (int(line_array[2]) * 4 / 10) #times 4 because of the 0.025Ohm resistor; mV div by current divider Ohm of resistor = mA
        # else:
        #     print("too short")

        # power = decoded_amp * decoded_busvoltage #in mW
        #
        #
        # num_lines += 1
        # if num_lines == 100:
        #     # write_to_file(time_array, busvoltage_data, shuntvoltage_data, amp_data)
        #     write_to_file(time_array, busvoltage_data, amp_data, power_data)
        #     # write_to_file(time_array, busvoltage_data, amp_data)
        #     num_lines=0
        #     time_array = []
        #     busvoltage_data = []
        #     # shuntvoltage_data = []
        #     amp_data = []
        #     power_data = []

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

    # results.close()
    port.close()
