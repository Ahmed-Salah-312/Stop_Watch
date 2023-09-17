#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char sec_units=0;          //1st digit of the seconds
unsigned char sec_tenth=0;          //2nd digit of the seconds
unsigned char min_units=0;          //1st digit of the minutes
unsigned char min_tenth=0;          //2nd digit of the minutes
unsigned char hr_units=0;           //1st digit of the hours
unsigned char hr_tenth=0;           //2nd digit of the hours
ISR(TIMER1_COMPA_vect)
{
	sec_units++;
	if(sec_units==10)
	{
		sec_tenth++;
		sec_units=0;
	}
	if(sec_tenth==6)
	{
		min_units++;
		sec_tenth=0;
	}
	if(min_units==10)
	{
		min_tenth++;
		min_units=0;
	}
	if(min_tenth==10)
	{
		hr_units++;
		min_tenth=0;
	}
	if(hr_units==10)
	{
		hr_tenth=0;
	}


}
void Timer1_Init(void)
{
	   // Set Timer1 to CTC (Clear Timer on Compare) mode
	    TCCR1B |= (1 << WGM12);

	    // Set the prescaler to divide clock by 1024
	    TCCR1B |= (1 << CS12) | (1 << CS10);

	    // Configure the compare value for 1 second interrupt
	    OCR1A = 976;  // (1 MHz / 1024) - 1

	    // Enable Timer1 compare interrupt
	    TIMSK |= (1 << OCIE1A);

	    // Enable global interrupts
	    sei();

}
ISR(INT0_vect)
{
	sec_units=0;
	sec_tenth=0;
	min_units=0;
	min_tenth=0;
	hr_units=0;
	hr_tenth=0;
}
/*Initialization of Interrupt 0 */
void INT0_Init(void)          
{
	MCUCR |= (1<<ISC01) ;
	MCUCR &= ~(1<<ISC00);
	GICR |= (1<<INT0);
	DDRD &=~ (1<<PD2);
	PORTD |= (1<<PD2);

}
ISR(INT1_vect)
{
	TCCR1B &= ~(1<<CS12) & ~(1<<CS10);

}

/*Initialization of Interrupt 1 */
void INT1_Init(void)
{
	 MCUCR |= (1<<ISC11) | (1<<ISC10);
	 GICR |= (1<<INT1);
	 DDRD &=~ (1<<PD3);

}
ISR(INT2_vect)
{
	TCCR1B |=(1<<CS12) | (1<<CS10);

}

/*Initialization of Interrupt 0 */
void INT2_Init(void)
{
	MCUCSR &= ~(1<< ISC2);
	GICR |= (1<<INT2);
	DDRB &=~ (1<<PB2);
    PORTB=0X04;

}

int main (void)
{
	SREG |=(1<<7);
	DDRC |= (0x0F);
	PORTC &= (0xF0);
	DDRA |= (0x3F);

	INT0_Init();
	INT1_Init();
	INT2_Init();
	Timer1_Init();
	while (1)
	{       /* Using multiplexing method */
		PORTA |=(1<<PA0);
		PORTC =(PORTC &0xF0) | (sec_units &0x0F);
		_delay_ms(2);
		PORTA &= ~(1<<PA0);

		PORTA |=(1<<PA1);
		PORTC =(PORTC &0xF0) | (sec_tenth &0x0F);
		_delay_ms(2);
		PORTA &= ~(1<<PA1);

		PORTA |=(1<<PA2);
		PORTC =(PORTC &0xF0) | (min_units &0x0F);
		_delay_ms(2);
		PORTA &= ~(1<<PA2);

		PORTA |=(1<<PA3);
		PORTC =(PORTC &0xF0) | (min_tenth &0x0F);
		_delay_ms(2);
		PORTA &= ~(1<<PA3);

		PORTA |=(1<<PA4);
		PORTC =(PORTC &0xF0) | (hr_units &0x0F);
		_delay_ms(2);
		PORTA &= ~(1<<PA4);

		PORTA |=(1<<PA5);
		PORTC =(PORTC &0xF0) | (hr_tenth &0x0F);
		_delay_ms(2);
		PORTA &= ~(1<<PA5);
	}
}
