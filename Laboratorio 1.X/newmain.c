/*
 * File:   newmain.c
 * Author: Leandro Cruz
 *
 * Created on 23 de febrero de 2021, 11:05 PM
 */

#include "config.h"
#include <xc.h>
#include "pic18f4550.h"
#define _XTAL_FREQ 4000000
int valor=0;

void InitPort()
{

   
   ADCON1bits.PCFG = 0xFF;
   TRISA = 0b000100;
   TRISB=0;
   TRISCbits.RC1=0;
   TRISD=0; //puertos d salidas
   
   
}

void main(void) 
{
    InitPort();
    LATD=0b00000000;
    
    if (PORTAbits.RA2==1)
    {
        valor++;
    }
    if(valor==1)
    { 
        LATD=0b10000001;
        __delay_ms(1000);
        LATD=0b01000010;
        __delay_ms(1000);
        LATD=0b00100100;
        __delay_ms(1000);
        LATD=0b00011000;
        __delay_ms(1000);
    }
    if(valor==2)
    {
        LATD=0b00000000;
        __delay_ms(1000);
        LATB=0b00000001;
        __delay_ms(3000);
        LATB=0b00000011;
        __delay_ms(3000);
        LATB=0b00000111;
        __delay_ms(3000);
        LATB=0b00001111;
        __delay_ms(3000);
        LATB=0b00011111;
        __delay_ms(3000);
        LATB=0b00111111;
        __delay_ms(3000);
        LATB=0b01111111;
        __delay_ms(3000);
        LATB=0b11111111;
        __delay_ms(3000);
        LATB=0b11111110;
        __delay_ms(3000);
        LATB=0b11111100;
        __delay_ms(3000);
        LATB=0b11111000;
        __delay_ms(3000);
        LATB=0b11110000;
        __delay_ms(3000);
        LATB=0b11100000;
        __delay_ms(3000);
        LATB=0b11000000;
        __delay_ms(3000);
        LATB=0b10000000;
        __delay_ms(3000);
    }
    if(valor==3)
    {
        LATA=0b000000;
        __delay_ms(1000);
        LATA=0b0000001;
        __delay_ms(1000);
        LATA=0b0001001;
        __delay_ms(1000);
        LATA=0b0001000;
        __delay_ms(1000);
        LATA=0b0011000;
        __delay_ms(1000);
        LATA=0b0011001;
        __delay_ms(1000);
        LATA=0b0010001;
        __delay_ms(1000);
        LATA=0b0010000;
        __delay_ms(1000);
        LATA=0b0110000;
        __delay_ms(1000);
        LATA=0b0110001;
        __delay_ms(1000);
        LATA=0b0111001;
        __delay_ms(1000);
        LATA=0b0111000;
        __delay_ms(1000);
        LATA=0b0101000;
        __delay_ms(1000);
        LATA=0b0101001;
        __delay_ms(1000);
        LATA=0b0100001;
        __delay_ms(1000);
        LATA=0b0100000;
        __delay_ms(1000);
    }
    if(valor==4)
    {
        PORTAbits.RA1=0;
        __delay_ms(1000);
        PORTAbits.RA1=1;
        __delay_ms(1000);           
    }
}
