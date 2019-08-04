/*
 Copyright (C) 2019 Elia Ritterbusch

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
*/

/*
This is a MODIFIED version of the i2c library made available by Elia Ritterbusch.
The original can be found here:
https://github.com/knightshrub/I2C-master-lib

Modifications:
- removing i2c_transmit and i2c_receive functions
- the i2c_readReg function has been split into the i2c_prepare_readReg and
	i2c_readReg functions
*/


#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#define I2C_READ 0x01
#define I2C_WRITE 0x00

void i2c_init(void);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_prepare_readReg(uint8_t devaddr, uint8_t regaddr);
uint8_t i2c_readReg(uint8_t* data, uint16_t length);
void i2c_stop(void);

#endif // I2C_MASTER_H
