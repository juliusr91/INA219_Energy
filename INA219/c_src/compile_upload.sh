avr-gcc -O3 -DF_CPU=16000000UL -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -mmcu=atmega328p -c -o main.o main.c
avr-gcc -O3 -DF_CPU=16000000UL -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -mmcu=atmega328p -c -o ina219.o ina219.c
avr-gcc -O3 -DF_CPU=16000000UL -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -mmcu=atmega328p -c -o  I2C-master-lib/i2c_master.o I2C-master-lib/i2c_master.c
avr-gcc -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -mmcu=atmega328p main.o ina219.o I2C-master-lib/i2c_master.o -o main
avr-objcopy -O ihex -R .eeprom main main.hex
#have to find port of arduino
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM1 -b 115200 -U flash:w:main.hex
