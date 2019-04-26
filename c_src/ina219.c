#include <avr/io.h>
#include <util/delay.h>
#include "ina219.h"
#include "I2C-master-lib/i2c_master.h"

uint8_t cal_val[2];

void get_bus_voltage(uint8_t *value){
  i2c_readReg((INA219_ADDRESS)<<1,INA219_REG_BUSVOLTAGE, value, 2);
}

// int16_t get_shunt_voltage(void){
void get_shunt_voltage(uint8_t *value){
  i2c_readReg((INA219_ADDRESS)<<1,INA219_REG_SHUNTVOLTAGE, value, 2);
}

void get_current(uint8_t *value) {
  cal_val[0]= 0x10;
  cal_val[1]= 0x00;

  i2c_writeReg((INA219_ADDRESS)<<1, INA219_REG_CALIBRATION, cal_val, 2);
  i2c_readReg((INA219_ADDRESS)<<1, INA219_REG_CURRENT, value, 2);
}

void init_ina219(void){
  /* sets up INA219 for 32V, 320mV gain, 12BIT ADC, 1 sample at 12BIT in continuous mode */
  // ina calibration
  cal_val[0]= 0x10;
  cal_val[1]= 0x00;


  i2c_writeReg((INA219_ADDRESS)<<1, INA219_REG_CALIBRATION, cal_val, 2);

  uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V | INA219_CONFIG_320_GAIN | INA219_CONFIG_BADCRES_12BIT
                    | INA219_CONFIG_SADCRES_1SAMPLE_12BIT | INA219_CONFIG_MODE_SANDBCONT;

  uint8_t conf8[2];
  conf8[0] = (uint8_t)(config>>8);
  conf8[1] = (uint8_t)(config);
  i2c_writeReg((INA219_ADDRESS)<<1, INA219_REG_CONFIG, conf8, 2);
}
