
// Watchdog Example
// 3/4/5
//
// In this example, we implement a simple binary counter
// If the counter is not incremented after a certain period of time,
// the watchdog will reset the count
//
// Alternate: After a certain time without a button press,
// The watchdog wil put the attiny85 into sleep mode


#include <avr/io.h>


uint8_t read_button(uint8_t pin){

    if(PINB&(1<<pin))
        return 1;
    else
        return 0;
}


int main(){

    // local counter variable
    uint8_t count = 0;

    // initialize PB0-PB3 as output pins
    DDRB = (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3);
    // initialize PB4 as an input pin (button)
    DDRB &= ~(1<<PB4);
    PORTB = 0;


    while(1){
    
    
        // wait for a button press
        while(read_button(PB4));
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
