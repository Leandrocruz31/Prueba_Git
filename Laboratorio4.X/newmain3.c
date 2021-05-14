/*
 * File:   newmain3.c
 * Author: Leandro Cruz
 *
 * Created on 28 de abril de 2021, 12:18 AM
 */


#include <xc.h>

#include <Sensor_Temperatura.h>

#define LCD_ENABLE_PIN PIN_B0 // ASIGNAMOS EL PIN "B0" COMO SALIDA PARA E
#define LCD_RS_PIN PIN_B1 // ASIGNAMOS EL PIN "B1" COMO SALIDA PARA RS
#define LCD_RW_PIN PIN_B2 // ASIGNAMOS EL PIN "B2" COMO SALIDA PARA RW
#define LCD_DATA4 PIN_B3 // ASIGNAMOS EL PIN "B3" COMO SALIDA PARA D4
#define LCD_DATA5 PIN_B4 // ASIGNAMOS EL PIN "B4" COMO SALIDA PARA D5
#define LCD_DATA6 PIN_B5 // ASIGNAMOS EL PIN "B5" COMO SALIDA PARA D6
#define LCD_DATA7 PIN_B6 // ASIGNAMOS EL PIN "B6" COMO SALIDA PARA D7
#include <lcd.c>

#FUSES NOWDT                    /*No Watch Dog Timer*/
#FUSES HS                       /*High speed Osc (> 4mhz)*/
#FUSES PUT                      /*Power Up Timer*/
#FUSES NOPROTECT                /*Code not protected from reading*/
#FUSES NOBROWNOUT               /*No brownout reset*/
#FUSES NOMCLR                    /*Master Clear pin enabled*/
#FUSES NOLVP                    /*No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O*/
#FUSES NOCPD


void main()
{
   lcd_init ();
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   float sensor=0;
   while(TRUE)
   {
     set_adc_channel (0);//lectura Vout del LM35 en PIN A0
          delay_us(1);
               sensor=read_adc();// sensor= variable que contendra Vout del LM35
               sensor=(sensor*4.88)/10;
                lcd_gotoxy (1,1);printf(LCD_PUTC, "TEMPERATURA");
         lcd_gotoxy (1,2);printf(LCD_PUTC, "%f Grados C  ",sensor);
   }

}