import serial
import os
import struct
import time

current_divider = 10

# def write_to_file(time_array, busvoltage_data, shuntvoltage_data, amp_data):
def write_to_file(time_array, busvoltage_data, amp_data, power):
# def write_to_file(time_array, busvoltage_data, amp_data):
    with open("data1.txt","a+") as b_file:
        # for line in zip(time_array, busvoltage_data, shuntvoltage_data, amp_data):
        for line in zip(time_array, busvoltage_data, amp_data, power):
        # for line in zip(time_array, busvoltage_data, amp_data):
            b_file.write(str(line)+"\n")

def get_serial_port():
    return "/dev/"+os.popen("dmesg | egrep ttyACM | cut -f3 -d: | tail -n1").read().strip()

def init_serial():
    port = serial.Serial(str(get_serial_port()), 500000, bytesize=8, parity='N', stopbits=2, timeout=None)
    time.sleep(5)
    print(port.get_settings())
    return port

def receive_data():
    time_array = []
    busvoltage_data = []
    # shuntvoltage_data = []
    amp_data = []
    power_data = []

    num_lines = 0
    send_start()
    while(True):
        time = port.read(2)
        decoded_time = struct.unpack("<H", time)[0]

        busvoltage = port.read(2)
        decoded_busvoltage = (struct.unpack("<H", busvoltage)[0] >> 3) * 4 * 0.001 #in V

        shuntvoltage = port.read(2)
        decoded_shuntvoltage = struct.unpack("<H", shuntvoltage)[0] *4  #(in mV) times 4 because of the 0.025Ohm resistor

        # amp = port.read(2)
        # decoded_amp = struct.unpack("<H", amp)[0] / current_divider #in mA
        decoded_amp = decoded_shuntvoltage/10 # mV div by current divider Ohm of resistor = mA
        power = decoded_amp * decoded_busvoltage #in mW

        time_array.append(decoded_time)
        busvoltage_data.append(decoded_busvoltage)
        # shuntvoltage_data.append(decoded_shuntvoltage)
        amp_data.append(decoded_amp)
        power_data.append(power)

        num_lines += 1
        if num_lines == 100:
            # write_to_file(time_array, busvoltage_data, shuntvoltage_data, amp_data)
            write_to_file(time_array, busvoltage_data, amp_data, power_data)
            # write_to_file(time_array, busvoltage_data, amp_data)
            num_lines=0
            time_array = []
            busvoltage_data = []
            # shuntvoltage_data = []
            amp_data = []
            power_data = []

def send_start():
    # start_byte = bytearray([240])
    num_bytes = port.write(b'\x40')
    port.flush()
    if num_bytes != 1:
        print("ERROR")
    else:
        print(num_bytes)

port = init_serial()
try:
    receive_data()
except KeyboardInterrupt:
    print('interrupted')

# results.close()
port.close()
