
/*
 * File:   newmain.c
 * Author: Leandro Cruz
 *
 * Created on 16 de abril de 2021, 12:13 PM
 */


#include <xc.h>
#include "pic18f4550.h"
#define _XTAL_FREQ 4000000

const char Display[10]={0000,0001,0010,0011,0100,0101,0110,0111,1000,1001};
int U=0,D=0;

int count=0;



void InitPort()
{
   ADCON1 = 0x0F;
   TRISC = 0; 
   TRISD = 0; 
}

void main(void) 
{
   while(1){
        InitPort();
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
   }
}

