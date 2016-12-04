// this program enables SPI communication and
// Sets the AVR into Slave mode
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_1MHz 0x00
#define F_CPU 1000000L //system clock frequency
#define BAUD 4800 // according to table 20-4, this gives error value of 0.2%
#define MYUBRR ((F_CPU/(16UL*BAUD))-1) //formula from table 20-1 : equation for calculating UBRRn in asynchronous normal mode
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

int toggle = 0;
int blink = 0;

void USART_Init(unsigned int ubrr)
{
 /* Set baud rate */
 UBRR0H = (unsigned char)(ubrr>>8); // write bit 15:8
 UBRR0L = (unsigned char)ubrr; // write bit 7:0
 /* Enable receiver and transmitter */
 UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
 /* Set frame format: 8data, 2stop bit */
 UCSR0C |= (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
}


unsigned int USART_Receive(void) {
 /* Wait for data to be received */
 while ( !(UCSR0A & (1<<RXC0)) ); //check if RXC0 flag is raised
 return UDR0; //register containing our data
}


void USART_Transmit(unsigned char data) {
 /* Wait for empty transmit buffer */
 while (!(UCSR0A & (1<<UDRE0))); //check if UDRE0 flag is raised
 /* Put data into buffer, sends the data */
 UDR0 = data;
}


void my_delay_ms(unsigned int delay) { //function for long delays
 unsigned int i;
 for (i = 0; i < delay/10; i++) {
 _delay_ms(10);
 }
}

void SPI_Init() {
 DDRB &= ~((1<<2)|(1<<3)|(1<<5)); // SCK, MOSI and SS as inputs
 DDRB |= (1<<4); // MISO as output
 SPCR &= ~(1<<MSTR); // Set as slave
 SPCR |= (1<<SPE); // enable SPI and interrupt
}

unsigned int SPI_Received(void) {
 while(!(SPSR & (1 << SPIF))); // wait until reception is completed
 return SPDR;
}

int main (void)
{
	USART_Init(MYUBRR);
	SPI_Init();
	DDRB = (1<<0); // init PB0 as output for LED
	PORTB = (0<<0); // init LED to off

	TCCR1A = 0; 		// init timer1 registers
	TCCR1B = 0;
	TCNT1 = 0; 			//init counter value to 0
	OCR1A = 487; 		//set CMR for (0.5 sec) 2Hz interrupts
	//turn on CTC mode, WGM13:0 = 0100, TCNT1 matches OCR1A value
	TCCR1B |= (1 << WGM12);
	//CS12:0 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);
	//enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	sei();		// enable interrupt

 while(1)
 {

	 int data = SPI_Received(); //Get character from BBB through SPI


	 USART_Transmit(data); // print command received to Serial Monitor
	 char *command;

	 if (data == 'S')
	 	toggle = 1;
	 else if (data == 'P')
	 	toggle = 0;
 }
}



// timer interrupt vector
ISR(TIMER1_COMPA_vect){
	// Disable interrupts in case of another interrupt
	cli();
	// toggle LED based on variable

	 if (toggle) {
	 	if (blink)  {
	 		PORTB = (1<<0); // LED on if enabled, otherwise LED always off
	 		blink = 0;
	 	}
	 	else {
	 		PORTB = (0<<0); // LED on if enabled, otherwise LED always off
	 		blink = 1;	
	 	}
	  }
	  else {
	  	 PORTB = (0<<0);
	  }

	// Re-enable interrupts
	sei();
}
