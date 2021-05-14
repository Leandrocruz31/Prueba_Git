/*
 * File:   newmain.c
 * Author: Leandro Cruz
 *
 * Created on 16 de abril de 2021, 12:13 PM
 */


#include <xc.h>
#include "pic18f4550.h"
#define _XTAL_FREQ 4000000

int contador=0;
int A = 0;
int B = 0;

void InitPort()
{
   TRISD = 0; //puertos d salidas
   TRISA = 0011;
   LATD = 00000000;
}

void main(void) 
{
    InitPort();
    PORTAbits.RA2 = 1;
    if(PORTAbits.RA0=1 && PORTAbits.RA1=0)
    {
       PORTAbits.RA2=1;
    }
    if(PORTAbits.RA0=1 && PORTAbits.RA1=0)
    {
       PORTAbits.RA3=1;
    }
}