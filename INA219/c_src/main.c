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
#include "defines.h"
#include <util/delay.h>
#include "I2C-master-lib/i2c_master.h"
#include "ina219.h"
#include <stdlib.h>


// setup USB UART
void setup_UART(unsigned int bittimer) {
  // baud rate registers (UBRRnH & UBRRnL)
  UBRR0H = (unsigned char) (bittimer >> 8);
  UBRR0L = (unsigned char) bittimer;
  // enable receiver and transmitter
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
  // set format --> 2 stop bits and 8 bit data
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

// transmitting to USB
void USART_Transmit(char data) {
  /* code */
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

void USART_Transmit_string(char *data) {
    /* code */
    uint8_t i = 0;
    while (data[i] != '\0')
        USART_Transmit (data[i++]);
}

// reading from USB
unsigned char USART_Read(void){
  while (!(UCSR0A & (1<<RXC0)));
  return UDR0;
}

// clock ticks
void init_timer(void) {
  TCCR1B = (1 << CS12);
}

int main(void) {
  /* code */
  // reading data from INA219
  uint8_t busvoltage[2];
  uint8_t shuntvoltage[2];
  busvoltage[1] = 0;
  busvoltage[0] = 0;
  shuntvoltage[1] = 0;
  shuntvoltage[0] = 0;

  // for transforming data and sending over UART
  int busv, shuntv;
  char char_voltage[5]; //
  char char_current[5];

  //timer vars
  volatile unsigned int long_timer = 0;
  volatile unsigned int old_ticks = 0;
  volatile unsigned int current_ticks = 0;
  char time_char[5];
  char char_long_timer[5];

  // setup UART
  setup_UART((CPU_FREQUENCY / UART_BAUD / 16) - 1); //for com with host device

  //init i2c, ina219 and timer
  i2c_init(); //for com with INA 219
  init_ina219();
  init_timer();

 while (1) {
//  prepare bus voltage register
   prepare_bus_voltage();

 // send shuntvoltage
   shuntv = (shuntvoltage[0] << 8) | (shuntvoltage[1] & 0xff); //most significant byte sent first by INA219
   itoa(shuntv, char_current, 10);
   USART_Transmit_string(char_current);
   USART_Transmit(EOL);

//  send time
   current_ticks = TCNT1;
   if (current_ticks < old_ticks) {
     long_timer++;
   }
   utoa(long_timer, char_long_timer, 10);
   USART_Transmit_string(char_long_timer);
   USART_Transmit(',');
   utoa(current_ticks, time_char, 10);
   USART_Transmit_string(time_char);
   USART_Transmit(',');

//  read bus voltage and prepare the shunt voltage register
   _delay_us(484); //required to make sure that the ADC is done. TODO: find more accurate delays
   read_bus_voltage(busvoltage);
   prepare_shunt_voltage();

//  send busvoltage
   busv = (busvoltage[0] << 8) | (busvoltage[1] & 0xff); //most significant byte sent first by INA219
   itoa(busv, char_voltage, 10);
   USART_Transmit_string(char_voltage);
   USART_Transmit(',');

//  wait and read shuntvoltage
   _delay_us(516);  //required to make sure that the ADC is done.
   read_shunt_voltage(shuntvoltage);
   old_ticks = current_ticks;
 }
}
