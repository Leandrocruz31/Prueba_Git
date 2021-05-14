char dc[10];
int cicloU1;
int ccp;  
int ccp1;

void Configuracion_Registros (void);
void Ciclo_Util (void);
void PWM (void);

void Configuracion_Registros (void)
{
    ADCON0=0;
    ADCON1=14;
    ADCON2=148;
    
}
void Ciclo_Util (void)
{
    ADCON0bits.ADON=1;
    ADCON0bits.GO_DONE=1;
    while (ADCON0bits.GO_DONE==1)
    {
        float dutycyclet=0;
        float dutycycle=0;
        
        dutycyclet=ADRESL+(ADRESH*256);
        dutycycle=dutycyclet*100/1023;
        cicloU1 = dutycycle;
        sprintf (dc, "%f", dutycycle);
        lcd_goto (0,2);
        lcd_print (dc);
        lcd_print ("%");
        lcd_print ("         ");
        
        
        
    }
    
}
void PWM (void){
//PWM periodo = (PR2 +1 )*4*Tosc*Prescaler // F = 10 KHz
// 1/10000 = (PR2 + 1)*4*1/4MHz * 1
// PR2 = ((1/10KHz)/(4/4MHz)*1) - 1
// PR2 = 99 ; PR2 = 99
    
 // PWM Duty Cycle = (CCPRXL:CCPXCON)* Tosc * TMR2 Pescaler value
 // CCPRXL:CCPXCON = PWM Duty Cycle / Tosc * TMR2 Pescaler value
    
    PR2 = 99;
    ccp = cicloU1;
    CCPR1L = ccp;
    TRISCbits.RC1=0;
    PORTCbits.RC1=0;
    TRISCbits.RC2=0;
    
    if(ccp >= 768 ){
        ccp1 = 3;
    }
    else if(ccp >= 512){   
        ccp1 =2;
    }
    else if(ccp >= 256){
        ccp1 = 1;
    }
    else {
        ccp1 = 0;
    }
    
    T2CON = 0x00;
    CCP1CON = (ccp1*16)+ 12;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
    

}