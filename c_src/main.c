#include <avr/io.h>
#include "defines.h"
#include <util/delay.h>
#include "I2C-master-lib/i2c_master.h"
#include "ina219.h"

void setup_UART(unsigned int bittimer) {
  /* code */
  UBRR0H = (unsigned char) (bittimer >> 8);
  UBRR0L = (unsigned char) bittimer;
  // enable receiver and transmitter
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
  // set format --> 2 stop bits and 8 bit data
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data) {
  /* code */
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

unsigned char USART_Read(void){
  while (!(UCSR0A & (1<<RXC0)));
  return UDR0;
}

void init_timer(void) {
  TCCR1B = (1 << CS12);
}



int main(void) {
  // DDRB |= _BV(DDB5);
  // PORTB |= _BV(PORTB5);
  /* code */
  uint8_t busvoltage[2];
  uint8_t shuntvoltage[2];
  // uint8_t current[2];
  unsigned int time = 0;
  /* set pin 5 high to turn led on */

  setup_UART((CPU_FREQUENCY / UART_BAUD / 16) - 1);
  //first need to init i2c and then ina219
  i2c_init();
  init_ina219();

  USART_Read();
  init_timer();
  _delay_ms(1000);


  while (1) {
    busvoltage[1] =0;
    busvoltage[0]=0;

    shuntvoltage[1]=0;
    shuntvoltage[0]=0;

    /* code */
    time = TCNT1;
    USART_Transmit(time);
    USART_Transmit((time>>8));

    //get voltage and transmit via UART
    get_bus_voltage(busvoltage);
    USART_Transmit(busvoltage[1]);
    USART_Transmit(busvoltage[0]);

    // get voltage and transmit via
    get_shunt_voltage(shuntvoltage);
    USART_Transmit(shuntvoltage[1]);
    USART_Transmit(shuntvoltage[0]);
  }
  return 0;
}
