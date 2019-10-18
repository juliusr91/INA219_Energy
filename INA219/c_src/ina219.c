/*
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
*/


#include <avr/io.h>
#include <util/delay.h>
#include "ina219.h"
#include "I2C-master-lib/i2c_master.h"


void prepare_bus_voltage(void){
    i2c_prepare_readReg((INA219_ADDRESS)<<1,INA219_REG_BUSVOLTAGE);
}

void read_bus_voltage(uint8_t *value){
    i2c_readReg(value, 2);
}


void prepare_shunt_voltage(void){
    i2c_prepare_readReg((INA219_ADDRESS)<<1,INA219_REG_SHUNTVOLTAGE);
}

void read_shunt_voltage(uint8_t *value){
    i2c_readReg(value, 2);
}


void init_ina219(void){

    // ina calibration
    uint8_t cal_val[2];
    cal_val[0]= 0x10;
    cal_val[1]= 0x00;
    i2c_writeReg((INA219_ADDRESS)<<1, INA219_REG_CALIBRATION, cal_val, 2);

    /* sets up INA219 for 32V, 320mV gain, 12BIT ADC, 1 sample at 12BIT in continuous mode */
    uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V | INA219_CONFIG_320_GAIN | INA219_CONFIG_BADCRES_12BIT
                    | INA219_CONFIG_SADCRES_1SAMPLE_12BIT | INA219_CONFIG_MODE_SANDBCONT;

    uint8_t conf8[2];
    conf8[0] = (uint8_t)(config>>8);
    conf8[1] = (uint8_t)(config);
    i2c_writeReg((INA219_ADDRESS)<<1, INA219_REG_CONFIG, conf8, 2);
}
