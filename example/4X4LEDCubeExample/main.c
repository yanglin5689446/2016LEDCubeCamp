
/***************************************************************************************
 *	函式中變數宣告請宣告於函式開頭
 *
 *
 ***************************************************************************************/
#include <regx51.h>

/****************************************************************************************
 *      don't edit this section
 *      不要修改以下這段code
 * *************************************************************************************/
#define DATA_PIN P1_0		//DS
#define CLOCK_PIN P1_1	//SHCP
#define LATCH_PIN P1_2 	//STCP
#define LAYER_1 P1_3
#define LAYER_2 P1_4
#define LAYER_3 P1_5
#define LAYER_4 P1_6

#define MSBFIRST 1
#define LSBFIRST 2
#define HIGH 1
#define LOW 0
#define ON 1
#define OFF 0

short LED[4];		//LED condition

/****************************************************************************************
 **函數: delay
 **輸入: x
 **輸出: 無
 **功能: delay 1ms
 **************************************************************************************/
void delay(unsigned int);

/****************************************************************************************
 **函數: shiftOut
 **輸入: BitOrder(LSB first or MSB first),val
 **輸出: 無
 **功能: shift out data to DS
 **************************************************************************************/
void shiftOut(unsigned char BitOrder,unsigned char val);
void clock_delay();
/****************************************************************************************
 *      you can call these function
 *      你可以使用以下函式
 **************************************************************************************/

/****************************************************************************************
 **函數: init
 **輸入: 無
 **輸出: 無
 **功能: configure AT89C51 and 74HC595
 * *************************************************************************************/
void init();

/****************************************************************************************
 **函數: turnOn
 **輸入: x,y,x (LED的座標)
 **輸出: 無
 **功能: turn on one LED in data
 *       在資料庫中開啟一個LED
 * *************************************************************************************/
void turnOn(unsigned char x, unsigned char y, unsigned char z);

/****************************************************************************************
 **函數: turnOff
 **輸入: x,y,x (LED的座標)
 **輸出: 無
 **功能: turn off one LED in data
 *       在資料庫中關閉一個LED
 **************************************************************************************/
void turnOff(unsigned char x, unsigned char y, unsigned char z);

/****************************************************************************************
 **函數: isOn
 **輸入: x,y,x (LED的座標)
 **輸出: 無
 **功能: check one LED is ON
 *       檢查一個LED是否開啟或關閉
 * *************************************************************************************/
unsigned char isOn(unsigned char x, unsigned char y, unsigned char z);

/****************************************************************************************
 **函數: display
 **輸入: times  (每層delay時間)
 **輸出: 無
 **功能: Starting Display LED cube by this function
 *       用這個函式開始顯示LED 方塊
 **************************************************************************************/
void display(unsigned char times);

/****************************************************************************************
 *      main function
 *      主函式
 ***************************************************************************************/
void main()
{
    //int x;
    init();
    while(1){
        turnOn(3,0,1);
        turnOn(1,1,1);
        turnOn(3,1,1);
        turnOn(1,2,1);
        turnOn(3,2,1);
        turnOn(1,3,1);
        turnOn(3,3,1);
        LED[2] = 0x5555;
        LED[3] = 0xAAAA;
        while(1){
		        display(0);
		    }
    }
}


/****************************************************************************************
 *      don't edit this section
 *      不要修改以下這段code
 * *************************************************************************************/
void delay(unsigned int x)
{
	unsigned int i,j;
	for (i = 0 ; i < x ; i++ )
		for (j = 0 ; j < 160 ; j++ );
}

void init()
{
    CLOCK_PIN = 0;
    LATCH_PIN = 1;
    DATA_PIN = 0;
    LAYER_1 = 0;
    LAYER_2 = 0;
    LAYER_3 = 0;
    LAYER_4 = 0;
    LED[0] = 0;
    LED[1] = 0;
    LED[2] = 0;
    LED[3] = 0;
}

void clock_delay()
{
    unsigned char i;
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
        //clock_delay();
        CLOCK_PIN = 1;
        //clock_delay();
        CLOCK_PIN = 0;
    }
}

void turnOn(unsigned char x, unsigned char y, unsigned char z)
{
    LED[z] |= ( 1 << ((y << 2)+x));
}

void turnOff(unsigned char x, unsigned char y, unsigned char z)
{
    LED[z] &= ~(1 << ((y<<2)+x));
}

unsigned char isOn(unsigned char x, unsigned char y, unsigned char z)
{
    return ( LED[z] >> (( y << 2 ) + x ) ) & 1 ;
}

void display(unsigned char times)
{
    volatile int iter;
    unsigned char high_byte,low_byte,tmp_p1;
    for (iter = 0 ; iter < 4 ; iter ++ ){
        high_byte = LED[iter] & 0xFF;
        low_byte =  LED[iter] >> 8;
        LATCH_PIN = 0;
        shiftOut(LSBFIRST,high_byte);
        shiftOut(LSBFIRST,low_byte);
        //LATCH_PIN = 1;  
            
        P2 = 0x00;
        switch(iter){
            case 0:
                P1 = 0x0C;
                break;
            case 1:
                P1 = 0x14;
                break;
            case 2:
                P1 = 0x24;
                break;
            case 3:
                P1 = 0x44;
                break;
            default:
                P2_1 = 1;
                break;
        }		
        delay(times);
    }
}
