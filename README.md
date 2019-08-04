# General
This is a collection of scripts for profiling the energy consumption of the
Odroid-XU4. The project is split into several sections for different measurement devices. It includes:
- Scripts for communicating betwee Otii and Odroid
- Scripts for the INA219 + Arduino for current and voltage measurements
- Several handy scripts to control the Odroid-XU4

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

The source code of all scripts / libraries is published under the GNU GPLv3, see LICENSE for details.
