#include <avr/io.h>
#include "defines.h"
#include <util/delay.h>
#include "I2C-master-lib/i2c_master.h"
#include "ina219.h"



// setup USB UART
void setup_UART(unsigned int bittimer) {
  /* code */
  UBRR0H = (unsigned char) (bittimer >> 8);
  UBRR0L = (unsigned char) bittimer;
  // enable receiver and transmitter
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
  // set format --> 2 stop bits and 8 bit data
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

// transmitting to USB
void USART_Transmit(unsigned char data) {
  /* code */
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

// reading from USB
unsigned char USART_Read(void){
  while (!(UCSR0A & (1<<RXC0)));
  return UDR0;
}

// needed for clock ticks
void init_timer(void) {
  TCCR1B = (1 << CS12);
}

// needed for com with Odroid
void setup_PB0(void){
  DDRB &= ~(1<<0);
  PORTB |= 1<<0; //enable pull up on PB0 port
}

void read_PB0(uint8_t * value){
  *value = 0;
  if ((PINB&(1<<0))==1){
    *value = 1;
  }
}



int main(void) {
  /* code */
  uint8_t busvoltage[2];
  uint8_t shuntvoltage[2];
  uint8_t value_odroid = 0;

  unsigned int time = 0;
  unsigned int time1 = 0;
  unsigned int time2 = 0;
  unsigned int time3 = 0;


  busvoltage[1] =0;
  busvoltage[0]=0;

  shuntvoltage[1]=0;
  shuntvoltage[0]=0;

  setup_UART((CPU_FREQUENCY / UART_BAUD / 16) - 1);
  setup_PB0();
  //first need to init i2c and then ina219
  i2c_init();
  init_ina219();

  USART_Read();
  // TODO: read if Odroid ready
  init_timer();
  _delay_ms(1000);

  //bogus first transmit
  USART_Transmit(time);
  USART_Transmit((time>>8));

  // USART_Transmit(time);
  // USART_Transmit((time>>8));


  USART_Transmit(busvoltage[1]);
  USART_Transmit(busvoltage[0]);

  USART_Transmit(value_odroid);

  while (1) {

    prepare_bus_voltage();
        // time1 = TCNT1;
    USART_Transmit(shuntvoltage[1]);
    USART_Transmit(shuntvoltage[0]);
    time = TCNT1;
    USART_Transmit(time);
    USART_Transmit((time>>8));
        // time2 = TCNT1;
        // time3 = time2 - time1;
        // USART_Transmit(time3);
        // USART_Transmit((time3>>8));

    _delay_us(484);
    read_bus_voltage(busvoltage);


    prepare_shunt_voltage();
    USART_Transmit(busvoltage[1]);
    USART_Transmit(busvoltage[0]);

    read_PB0(&value_odroid); //check if Odroid still wants measurement
    USART_Transmit(value_odroid); //temp for debug

    _delay_us(516);
    read_shunt_voltage(shuntvoltage);

    // TODO: interrupt from Odroid
  }
  return 0;
}
