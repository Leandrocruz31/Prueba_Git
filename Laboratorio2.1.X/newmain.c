/*
 * File:   newmain.c
 * Author: Leandro Cruz
 *
 * Created on 15 de marzo de 2021, 09:03 PM
 */

#include <xc.h>

#pragma config FOSC= XT_XT
#pragma config CPUDIV= OSC1_PLL2

void main(void) {

    TRISA=1;
    TRISB=0b11111110;
    TRISD=0b11111111;
    ADCON0=0b0000;

    ADCON1bits.PCFG=0b00000000;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    ADCON2bits.ACQT=2;
    ADCON2bits.ADCS=2;
    ADCON2bits.ADFM=0;// datos izquierda
    ADCON0bits.ADON=1; // conversor analogo digital

    while(1){

        ADCON0bits.GO_DONE=1;

            float c=ADRESH; // almacenar los datos de adresh solo 8bits
            double a;//almacenar datos grados °f
            double c2;//almacenar datos grados °c
            int puerto;
         c2= (100*c*5)/255;  //formula lm25 datos adresh a °c . 255=8bits
         a=(c2*1.8)+32; //formula de °c a°f

         if(a<150){
             if(PORTD==0b00000101  PORTD==0b00000010 ){
                 PORTBbits.RB0=1;

             }

             else{
                PORTBbits.RB0=0;
             }
         }
           else {

             if(PORTD==0b00000100  PORTD==0b00000011){
                 PORTBbits.RB0=1;

         }
             else{
                PORTBbits.RB0=0;
             }
           }

        }


    return;
}
