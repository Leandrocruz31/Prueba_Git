/*
 * File:   newmain.c
 * Author: Leandro Cruz
 *
 * Created on 23 de febrero de 2021, 11:05 PM
 */

#include "confi.h"
#include <xc.h>
#include "pic18f4550.h"
#define _XTAL_FREQ 4000000
 

void main(void) {

    int p; //Variable potenciometro 
    int conv;//Variable de los cajones
    int v;//voltaje 


    
    ADCON1=0b00000111 ;// Registro binaro 8 bits

    TRISD=0b00000000 ;//Salidas
    PORTD=0b00000000 ;//Puerto 
    TRISA=0b00000001 ;//potenciometro como entrada
    PORTA=0b00000000 ;//apagados

    ADCON0=0b00000001 ;//Conversion A/D

    ADCON2=0b10010100 ;//Configuracion derecha , tiempo , ecuacion 

    TRISB=0b00000000 ; //
    PORTB=0b00000000 ;

    while (1){

        ADCON0bits.CHS=0x00; //Seleccion canal
        ADCON0bits.GO_DONE=1;//Inicializa la conversion

        conv=((ADRESH*256)+ADRESL) ;//Cajones

          v=(conv+0.0)/(1023)*(50) ;

                PORTD=((v/10)*16)+(v%10) ;

                if (v<35){

                   PORTBbits.RB0=0;

                }
                else {
                    
                   PORTBbits.RB0=1;
                    
                }
           }

    return;
}