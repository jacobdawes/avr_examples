// main

#include <avr/io.h>
#include <util/delay.h>

int main(){

	DDRB = 0b11111111;
	
while(1){


	PORTB |= (1<<3);
	_delay_ms(500);
	PORTB &= ~(1<<3);
	_delay_ms(500);
}

}
