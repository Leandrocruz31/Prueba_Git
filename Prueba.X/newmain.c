/*
 * File:   newmain.c
 * Author: Leandro Cruz
 *
 * Created on 24 de febrero de 2021, 07:54 PM
 */




#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 4000000

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)




void main(void) 
{
PORTCbits.RC7 = 1; //entradas
TRISD = 0x00; //salidas

PORTC = 0x00;
PORTD = 0x00;

while(1){

if (PORTCbits.RC7== 1){
PORTDbits.RD1=1;}

if (PORTCbits.RC7== 0){
PORTDbits.RD1=0;}
}   
}

