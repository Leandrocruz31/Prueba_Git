/*
 * File:   newmain.c
 * Author: Leandro Cruz
 *
 * Created on 13 de mayo de 2021, 10:18 PM
 */


#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#include "LCD.h"
#include "Configuracion.h"


void main (void){
    TRISAbits.RA0 = 1;
    TRISCbits.RC2 = 0;
    Configuracion_Registros();
    lcd_init ();
    lcd_clear_display();
    lcd_cursor_home();
    lcd_print ("Duty Cycle:");
    lcd_goto (0,2);
    lcd_print ("0%"); 
    while (1)
    {
        Ciclo_Util ();
        __delay_ms (100);
        PWM();
    }
    return; 
}
