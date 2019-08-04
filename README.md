# General
This is a collection of scripts for profiling the energy consumption of the
Odroid-XU4. The project is split into several sections for different measurement devices.
The Otii device, the INA219 + Arduino  and a couple handy commands for the Odroid-XU4.

## Otii
We use the Otii by qoitech - https://www.qoitech.com/
The Odroid communicates over UART - the scripts show how to do the communications.

## INA219
A collection of scripts for a combination of INA219 and Arduino
TODO: include interrupts from the Odroid

## Odroid-XU4
Scripts to manage settings on the Odroid including:
- Fan settings
- DVFS
- Flushing L1 and L2 Cache
- Disabling L2 Cache
- Disabling cores

-----

License

The source code of I2C-Master-lib is published under the GNU GPLv3, see LICENSE for details.
