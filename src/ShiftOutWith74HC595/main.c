
#include<regx51.h>
#include<8051ShiftOut.h>

#define LATCH_PIN P1_2		//STCP

void delay(int x)
{
	int i,j;
	for ( i = 0 ; i < x ; i ++ )
		for (j = 0 ; j < 160 ; j ++);
}

void main()
{
	CLOCK_PIN = 0;
	DATA_PIN = 0;
	LATCH_PIN = 1;
	delay(100);
	while(1){
		unsigned char val;
		for (val = 0 ; val < 256 ; val++){
			P1_2 = 0;
			shiftOut(LSBFIRST,val);
			P1_2 = 1;
			delay(1000);
		}
	}
}