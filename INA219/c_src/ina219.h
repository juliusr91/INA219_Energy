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


//INA Stuff
#define INA219_ADDRESS (0x40)
#define INA219_READ (0x01)
#define INA219_REG_CONFIG (0x00)
#define INA219_CONFIG_RESET (0x8000) // Reset Bit
#define INA219_REG_CALIBRATION (0x05)

//setup bits
#define INA219_CONFIG_BVOLTAGERANGE_32V (0x2000) //Bit voltage mask set to 32V
#define INA219_CONFIG_320_GAIN (0x1800) // Gain Mask set at 320mV
#define INA219_CONFIG_BADCRES_12BIT (0x0180) // Bus ADC Resolution set to 12 bit
#define INA219_CONFIG_SADCRES_1SAMPLE_12BIT (0x0018)  // Shunt ADC Resolution and Averaging Mask set to 1 * 12 bit sample
#define INA219_CONFIG_MODE_SANDBCONT (0x0007) // Operating Mode Mask set to s and b volt continuos

// registers for reading
#define INA219_REG_SHUNTVOLTAGE (0x01)
#define INA219_REG_BUSVOLTAGE (0x02)
#define INA219_REG_CURRENT (0x04)

// to interpret data properly

#define INA219_CURRENT_DIV_MA 10
#define INA219_POWER_MULT_MW 2


void init_ina219(void);
void get_bus_voltage(uint8_t *value);
void get_shunt_voltage(uint8_t *value);
void get_current(uint8_t *value);

//overlap request and UART
void prepare_bus_voltage(void);
void read_bus_voltage(uint8_t *value);
void prepare_shunt_voltage(void);
void read_shunt_voltage(uint8_t *value);
