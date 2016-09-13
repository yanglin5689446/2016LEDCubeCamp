
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

typedef unsigned char byte;		//8 bits
short LED[4];		//LED condition

/****************************************************************************************
 **函數: delay
 **輸入: x
 **輸出: 無
 **功能: delay 1ms
 * *************************************************************************************/
void delay(unsigned int);

/****************************************************************************************
 **函數: shiftOut
 **輸入: BitOrder(LSB first or MSB first),val
 **輸出: 無
 **功能: shift out data to DS
 * *************************************************************************************/
void shiftOut(unsigned char BitOrder,unsigned char val);

/****************************************************************************************
 *      you can call these function
 *      你可以使用以下函式
 * *************************************************************************************/

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
void turnOn(byte x, byte y, byte z);

/****************************************************************************************
 **函數: turnOff
 **輸入: x,y,x (LED的座標)
 **輸出: 無
 **功能: turn off one LED in data
 *       在資料庫中關閉一個LED
 * *************************************************************************************/
void turnOff(byte x, byte y, byte z);

/****************************************************************************************
 **函數: isOn
 **輸入: x,y,x (LED的座標)
 **輸出: 無
 **功能: check one LED is ON
 *       檢查一個LED是否開啟或關閉
 * *************************************************************************************/
unsigned char isOn(byte x, byte y, byte z);

/****************************************************************************************
 **函數: display
 **輸入: times  (每層delay時間)
 **輸出: 無
 **功能: Starting Display LED cube by this function
 *       用這個函式開始顯示LED 方塊
 * *************************************************************************************/
void display(byte times);

/****************************************************************************************
 *      main function
 *      主函式
 ***************************************************************************************/
void main()
{
    init();
    display(1);
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

void turnOn(byte x, byte y, byte z)
{
    LED[z] |= ( 1 << ((y << 2)+x));
}

void turnOff(byte x, byte y, byte z)
{
    LED[z] &= ~(1 << ((y<<2)+x));
}

unsigned char isOn(byte x, byte y, byte z)
{
    /*if (( LED[z] >> (( y << 2 ) + x ) ) & 1)
        return ON;
    else
        return OFF;*/
    return ( LED[z] >> (( y << 2 ) + x ) ) & 1 ;
}

void display(byte times)
{
    unsigned char i;
    for (i = 1 ; i <= 4 ; i ++ ){
        unsigned char high_byte = LED[i] & 0xFF;
        unsigned char low_byte =  LED[i] >> 8;
        LATCH_PIN = 0;
        shiftOut(LSBFIRST,high_byte);
        shiftOut(LSBFIRST,low_byte);
        LATCH_PIN = 1;  
        P1 = P1 & 0xE0;
        /*
          P1 |= 1 << (i+3);
        */
        switch(i){
            case 1:
                LAYER_1 = 1;
                break;
            case 2:
                LAYER_2 = 1;
                break;
            case 3:
                LAYER_3 = 1;
                break;
            case 4:
                LAYER_3 = 1;
                break;
        }
        delay(times);
    }
}
