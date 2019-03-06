
// Watchdog Example
// 3/4/5
//
// In this example, we implement a simple binary counter
// 
// If the counter is not incremented after a certain period of time,
// the watchdog will first trigger an interrupt, flashing the lights on the port
// 
// The watchdog timer is configured while the flashing occurs
// When this timer is done, the device will reset


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>



// Interrupt service routine for watchdog timer interrupt
ISR(WDT_vect){

    // Set all of the pins high as a warning
    PORTB |= 0b00001111;
}



// Read pin value and output true/false result
uint8_t read_button(uint8_t pin){

    if(PINB&(1<<pin))
        return 1;
    else
        return 0;
}



// Configure watchdog in interrupt mode
void wdt_config_int(){

    // Enable watchdog interrupts
    WDTCR |= (1<<WDIE);
    // Set watchdog change enable bit before configuring prescaler bits
    WDTCR |= (1<<WDCE);
    // Configure prescaler for a 4 second timeout
    WDTCR |= (1<<WDP3);
}


void wdt_config_reset(){

    //
}



int main(){

    // Local counter variable
    uint8_t count = 0;

    // Initialize PB0-PB3 as output pins
    DDRB = (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3);
    // Initialize PB4 as an input pin (button)
    DDRB &= ~(1<<PB4);
    PORTB = 0;

    // Configure the watchdog timer to interrupt (not reset) after 4 seconds
    sei();
    wdt_config_int();


    while(1){
    
    
        // wait for a button press
        while(read_button(PB4));
        wdt_reset();
        _delay_ms(50);
        // once the button press occurs, increment counter
        if(count<16)
            count++;
        else
            count = 0;

        // display count on output register
        PORTB = count;
    }

    return 0;
}
