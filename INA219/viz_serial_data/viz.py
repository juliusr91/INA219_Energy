'''
Copyright (C) 2019 Julius Roeder

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


import matplotlib.pyplot as plt

tick_overflow = 2**16 #number of ticks before reset
num_ticks = 16000000/256 #number of ticks per second

watt = []
ticks = []
time = [0]
total_time = 0

with open("../serial_read/data1.txt", "r") as file:
    for line in file:
        ticks.append(int(line.split(",")[0][1:]))
        watt.append(float(line.split(",")[3][:-2]))

for i, tick in enumerate(ticks[1:]):
    diff = tick - ticks[i]
    if diff < 0:
        diff = tick_overflow - ticks[i]
        diff = diff + tick

    time_diff = diff/num_ticks
    total_time = total_time + time_diff
    time.append(total_time)


plt.plot(time, watt)
plt.show()
