#include <pic18f4550.h>
#include <xc.h>
#define _XTAL_FREQ 4000000
#pragma config FOSC = XT_XT


void main(void) {
    //CONFIGURACION DE PUERTOS
    TRISD = 0;
    TRISC = 0;
    TRISA = 1;
    ADCON1 = 0x0F;
   
    //CONVERSION DE NUMEROS 
  unsigned char tabla[10] = {126,12,182,158,204,218,250,14,254,222};
  unsigned int decena, unidad, cuenta;
  
  cuenta = 0 ;
  
  while(1){
      
      
      //CONVERSION
      decena = cuenta/10;
      unidad = cuenta%10;
      
      
      PORTD = (tabla[decena]);
      PORTCbits.RC0 = 1;

      PORTCbits.RC0 = 0;
      __delay_ms(10);
      
      PORTD = (tabla[unidad]);
      PORTCbits.RC1 = 1;
      __delay_ms(10);
      PORTCbits.RC1 = 0;
      __delay_ms(10);
      
     if(PORTAbits.RA0 == 1){
          while(PORTAbits.RA0 == 1){
      PORTD = (tabla[decena]);
      PORTCbits.RC0 = 1;
      __delay_ms(10);
      PORTCbits.RC0 = 0;
      __delay_ms(10);
      
      PORTD = (tabla[unidad]);
      PORTCbits.RC1 = 1;
      __delay_ms(10);
      PORTCbits.RC1 = 0;
      __delay_ms(10);
          }
      cuenta++;
      }
      
      if(PORTAbits.RA1 == 1){
      while(PORTAbits.RB1 == 1){
      PORTD = (tabla[decena]);
      PORTCbits.RC0 = 1;
      __delay_ms(10);
      PORTCbits.RC0 = 0;
      __delay_ms(10);
      
      PORTD = (tabla[unidad]);
      PORTCbits.RC1 = 1;
      __delay_ms(10);
      PORTCbits.RC1 = 0;
      __delay_ms(10);
          }
      cuenta--;
      }

      if(cuenta > 99){
          cuenta = 0;
      } 
    
  }
  
}