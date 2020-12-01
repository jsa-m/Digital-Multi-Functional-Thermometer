/*******************************************************************
/* file name : four7Seg.c 
/*******************************************************************
/* description    : Driver for four seven segment displays 
/*                  common anode and multiplexed. 
/* programmer     : Joaquin Sopena 
/* lenguage       : ANSI C 
/* date           : October 25, 2020
/********************************************************************/

#include "Arduino.h"

/******************************************************************************/
/*                        Local variables                                     */
/******************************************************************************/

int num7seg[] = { B11000000, B11111001, B10100100, B10110000,
                  B10011001, B10010010, B10000010, B11111000,
                  B10000000, B10011000};
//Display is connected to pins 0 to 7 of the Arduino, this array contains
//the combinations for numbers 0 to 9.

int count_seg = 4;	//Value to manage multiplexing


/******************************************************************************/
/*                       Functions                                            */
/******************************************************************************/

//Converts a decimal number to its equivalent for seven segment displays
//Values from 0 to 999 with one decimal.

void splitnumber(float value, int *h, int *t, int *u, int *th)
{
    int tens, units, tenths;
    int temp = (int)value;
    float tempth;
    if(value < 1000) //If not, error.
    {
        *h = temp / 100;
        *th = (int)((value - temp)*10);
        temp = temp % 100;
        *t = temp / 10;
        *u = temp % 10;
    }
}

void multiplexDisplay(float value, int a, int b, int c, int d)
{
    if(count_seg == 4 & value > 99){
        PORTB = B11111110;
        PORTD = num7seg[a];
    }
    if(count_seg == 3 & value > 9){
        PORTB = B11111101;
        PORTD = num7seg[b];
    }
    if(count_seg == 2){
        PORTB = B11111011;
        PORTD = num7seg[c] & B01111111;
    }
    if(count_seg == 1){
        PORTB = B11110111;
        PORTD = num7seg[d];
        count_seg = 5;
    }
    count_seg -=1;
}

void initDisplay()
{
    DDRD = B11111111;	//Set Arduino digital pins 0 to 7 as output
    DDRB = B00001111;	//Set Arduino digital pin 8-11 as output
}
