
#ifndef SHIFTOUT_H
#define SHIFTOUT_H

#include<regx51.h> 

//DS
#ifndef DATA_PIN
    #define DATA_PIN P1_0
#endif

//SHCP
#ifndef CLOCK_PIN
    #define CLOCK_PIN P1_1
#endif

#define MSBFIRST 1
#define LSBFIRST 2

/*
 *  delay for pin physical voltage operation
 */
void clock_delay()
{
    unsigned i;
    for (i = 0 ; i < 5 ; i++);
}

void shiftOut(unsigned char BitOrder,unsigned char val)
{
    unsigned char i;
    for (i = 0 ; i < 8 ; i++){
        if (BitOrder == LSBFIRST)
            DATA_PIN = !!(val & (1<<i));
        else
            DATA_PIN = !!(val & (1<<(7-i)));
        clock_delay();
        CLOCK_PIN = 1;
        clock_delay();
        CLOCK_PIN = 0;
    }
}

#endif
