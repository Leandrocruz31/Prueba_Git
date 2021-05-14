/*
 * File:   newmain.c
 * Author: Leandro Cruz
 *
 * Created on 16 de abril de 2021, 12:13 PM
 */


#include <xc.h>
#include "pic18f4550.h"
#define _XTAL_FREQ 4000000
#pragma config FOSC = XT_XT

unsigned char Display[10]={0b0000,0b0001,0b0010,0b0011,0b0100,0b0101,0b0110,0b0111,0b1000,0b1001};
int U = 0;
int D = 0;

int count=0;

void main(void) 
{
   ADCON1 = 0x0F;
   TRISC = 0; 
   TRISD = 0; 
   count=0;
   while(1){

        D = count/10;
        U = count%10;
        

          PORTD = (Display[D]);
          __delay_ms(10);
          PORTD = (Display[U]);
          __delay_ms(10);


          if(PORTBbits.RB0 == 1)
          {
          PORTD = (Display[D]);
          PORTD = (Display[U]);
          __delay_ms(10);
          count++;
          }

          if(PORTBbits.RB1 == 1)
          {
          PORTD = (Display[D]);
          PORTD = (Display[U]);
          __delay_ms(10);
          count--;
          }

          if(count > 99){
              count = 0;
          } 
          if(count >= 30)
          {
             PORTBbits.RB3 == 1;
          }
   }
}
