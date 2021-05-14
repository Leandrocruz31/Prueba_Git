/*
 * File:   newmain2.c
 * Author: Leandro Cruz
 *
 * Created on 16 de abril de 2021, 05:45 PM
 */

#include <xc.h>
#include "pic18f4550.h"
#define _XTAL_FREQ 4000000
#pragma config FOSC = XT_XT

int display[10] = {0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0100111, 0b1111111, 0b1101111};

int unidad = 0;
int decena = 0;

int cuenta=0;

void main(void) 
{
   ADCON1 = 0x0F;
   TRISA = 0b0011;//bits de salidas led y entradas de señal
   TRISD = 0; //poner el puerto D en salidas
   TRISB = 0; //poner puerto B en salidas

   while(1)
   { 
       //Imprimir display
       LATD = (display[unidad]);
       LATB = (display[decena]);
       
       if(cuenta>=30)//cuando la cuenta sea mayor a 30 prender led de alarma
       {
           PORTAbits.RA2=0;
           PORTAbits.RA3=1;
       }
       if(cuenta<30)//cuando la cuenta sea menor a 30 mantener led verde
       {
           PORTAbits.RA2=1;
           PORTAbits.RA3=0;
       }
       //Incremento
       if(PORTAbits.RA0==1)//Cuando se presione el boton incrementar cuenta
       {
            unidad=unidad++;
            cuenta++;
            __delay_ms(300);
       }
       
       if(unidad>=10)//Cuando la unidad sea mayor de 10 aunmentar decena
       {
           unidad=0;
           decena=decena++;
       }
       if(decena>=10)//Cuando la decena sea mayor a 10 colocar decena en 0
       {
           decena=0;
       }
       
       //Decrecimiento
       if(PORTAbits.RA1==1)//Cuando se presione el boton decrementa cuenta
       {
           unidad=unidad--;
           cuenta--;
           __delay_ms(300);
       }
       if(unidad<0)//Cuando la unidad sea menor a 0 disminuir la decena 
       {
           unidad=9;
           decena=decena--;
       }
       if(decena<0)//Cuando la decena sea menor a 0 colocar decena 9
       {
           decena=9;
       }
   }
}