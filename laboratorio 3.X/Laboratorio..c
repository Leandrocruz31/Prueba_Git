

#include <xc.h>
#include "pic18f4550.h"
#define _XTAL_FREQ 4000000
#pragma config PLLDIV=1
#pragma config FOSC=XT_XT

int num=0;
char opc='A';
int Nant=0;
int Nact=0;
int x=0;//Numero B
int y=0;//Numero A
int cont=0;
int cont1=0;

void Configuracion_Registros (void);
void Temp (void); //Funcion de temportizador
void B (int);//display B
void A (int);//Display A
void creg (int, int);
void main(void) 
{
    TRISA=9;
    TRISB=255;
    TRISC=0;
    TRISD=0;
    TRISE=8;
    PORTA=0;
    PORTB=0;
    PORTC=0;
    PORTD=0;
    PORTE=0;
    
    Configuracion_Registros ();
        
    while (1)
    {
        PORTC=6;
        PORTC=5;
        PORTC=3;
        Temp ();//Funcion de temporizador 
        switch (opc)
        {
            case '*'://cuando se pulse * iniciar conteo
            {
                PORTDbits.RD5=0;
                PORTDbits.RD6=1;
                for (Nant; Nant>=0; Nant--)
                {
                    A (Nant);
                    if (cont==0)
                    {
                        for (Nact; Nact>=0; Nact--)
                        {
                            B (Nact);
                            __delay_ms(300);
                        }
                        cont=1;
                    }
                    else
                    {
                    for (int i=9; i>=0; i--)
                        {
                            B (i);
                            Nact=i;
                            __delay_ms(300);
                        }
                    }
                }
                Nant=0;
                Nact=0;
                num=0;
                PORTDbits.RD6=0;
                opc='0';//cuando llegue a 0 romper el caso
                break;
            }
            default:
            {
                if (cont1==1)
                {
                    x=num;
                    Nact=x;
                    B (Nact);
                    y=Nact;
                    cont1++;
                }
                else if (cont1%2==1)
                {
                    Nant=y;
                    A (Nant);
                    x=num;
                    Nact=num;
                    B (Nact);
                    y=Nact;
                    cont1++;
                }
                break;
            }
            opc='A';
        }
    }
    return;
}
void Configuracion_Registros (void)
{
    ADCON0=0;
    ADCON1=0X1B;
    ADCON2=148;
    
    INTCONbits.GIE=0;
    INTCONbits.INT0IE=1;
    INTCON3bits.INT1IE=1;
    INTCONbits.RBIE=1;
    INTCON2bits.INTEDG0=1;
    INTCON2bits.INTEDG1=1;
    INTCON2bits.INTEDG2=1;    
    RCONbits.IPEN=1;
    INTCONbits.GIEH=1;
    INTCONbits.GIEL=1;
    INTCON3bits.INT1IP=1;
    INTCON3bits.INT2IP=0;
    INTCON2bits.RBIP=0;
    INTCON2bits.NOT_RBPU=0;
    INTCONbits.INT0IF=0;
    INTCON3bits.INT1IF=0;    
    INTCON3bits.INT2IF=0;
    INTCONbits.RBIF=0;
}
void Temp (void)
{
    ADCON0bits.ADON=1;
    ADCON0bits.GO_DONE=1;//inicializa la conversion
    while (ADCON0bits.GO_DONE==1)//mientras el tiempo de conversion
    {
        float tempt=0;
        float temp=0;
        
        tempt=ADRESL+(ADRESH*256);
        temp=(tempt+1)*150/1024;
        
        if (temp>60)
        {
            PORTDbits.RD4=1;
            PORTDbits.RD7=1;
        }
        else
        {
            PORTDbits.RD4=0;
            PORTDbits.RD7=0;
        }
    }
}
void B (int x)
{
    if (x==0)//Numero 0
    {
        PORTDbits.RD0=0;
        PORTDbits.RD1=0;
        PORTDbits.RD2=0;
        PORTDbits.RD3=0;
    }
    else if (x==1)//Numero 1
    {
        PORTDbits.RD0=1;
        PORTDbits.RD1=0;
        PORTDbits.RD2=0;
        PORTDbits.RD3=0;
    }
    else if (x==2)//Numero 2
    {
        PORTDbits.RD0=0;
        PORTDbits.RD1=1;
        PORTDbits.RD2=0;
        PORTDbits.RD3=0;
    }
    else if (x==3)//Numero 3
    {
        PORTDbits.RD0=1;
        PORTDbits.RD1=1;
        PORTDbits.RD2=0;
        PORTDbits.RD3=0;
    }
    else if (x==4)//Numero 4
    {
        PORTDbits.RD0=0;
        PORTDbits.RD1=0;
        PORTDbits.RD2=1;
        PORTDbits.RD3=0;
    }
    else if (x==5)//Numero 5
    {
        PORTDbits.RD0=1;
        PORTDbits.RD1=0;
        PORTDbits.RD2=1;
        PORTDbits.RD3=0;
    }
    else if (x==6)//Numero 6
    {
        PORTDbits.RD0=0;
        PORTDbits.RD1=1;
        PORTDbits.RD2=1;
        PORTDbits.RD3=0;
    }
    else if (x==7)//Numero 7
    {
        PORTDbits.RD0=1;
        PORTDbits.RD1=1;
        PORTDbits.RD2=1;
        PORTDbits.RD3=0;
    }
    else if (x==8)//Numero 8
    {
        PORTDbits.RD0=0;
        PORTDbits.RD1=0;
        PORTDbits.RD2=0;
        PORTDbits.RD3=1;
    }
    else if (x==9)//Numero 9
    {
        PORTDbits.RD0=1;
        PORTDbits.RD1=0;
        PORTDbits.RD2=0;
        PORTDbits.RD3=1;
    }
}
void A (int y)
{
    if (y==0)//Numero 0
    {
        PORTAbits.RA4=0;
        PORTAbits.RA5=0;
        PORTEbits.RE0=0;
        PORTEbits.RE1=0;
    }
    else if (y==1)//Numero 1
    {
        PORTAbits.RA4=1;
        PORTAbits.RA5=0;
        PORTEbits.RE0=0;
        PORTEbits.RE1=0;
    }
    else if (y==2)//Numero 2
    {
        PORTAbits.RA4=0;
        PORTAbits.RA5=1;
        PORTEbits.RE0=0;
        PORTEbits.RE1=0;
    }
    else if (y==3)//Numero 3
    {
        PORTAbits.RA4=1;
        PORTAbits.RA5=1;
        PORTEbits.RE0=0;
        PORTEbits.RE1=0;
    }
    else if (y==4)//Numero 4
    {
        PORTAbits.RA4=0;
        PORTAbits.RA5=0;
        PORTEbits.RE0=1;
        PORTEbits.RE1=0;
    }
    else if (y==5)//Numero 5
    {
        PORTAbits.RA4=1;
        PORTAbits.RA5=0;
        PORTEbits.RE0=1;
        PORTEbits.RE1=0;
    }
    else if (y==6)//Numero 6
    {
        PORTAbits.RA4=0;
        PORTAbits.RA5=1;
        PORTEbits.RE0=1;
        PORTEbits.RE1=0;
    }
    else if (y==7)//Numero 7
    {
        PORTAbits.RA4=1;
        PORTAbits.RA5=1;
        PORTEbits.RE0=1;
        PORTEbits.RE1=0;
    }
    else if (y==8)//Numero 8
    {
        PORTAbits.RA4=0;
        PORTAbits.RA5=0;
        PORTEbits.RE0=0;
        PORTEbits.RE1=1;
    }
    else if (y==9)//Numero 9
    {
        PORTAbits.RA4=1;
        PORTAbits.RA5=0;
        PORTEbits.RE0=0;
        PORTEbits.RE1=1;
    }
}
void __interrupt(high_priority) ISR_EX0_1(void)//Funcion de mantenimiento
{
    if (INTCONbits.INT0IF==1)//Cuando el bit RB1 sea 1 iniciar codigo
    {
        INTCONbits.INT0IF=0;//Cuando el bit RB0 sea 0 
        for (int i=0; i<10; i++)
        {
            B(i);//Conteo de 1 a 9 en el display
            __delay_ms(500);
        }
        B(0);//reiniciar display B
        A(0);//reiniciar display A
        for (int i=0; i<3; i++)
        {
            PORTDbits.RD5=1;//prender leds
            PORTDbits.RD6=1;
            PORTDbits.RD7=1;
            __delay_ms(300);
            PORTDbits.RD5=0;//apagar leds
            PORTDbits.RD6=0;
            PORTDbits.RD7=0;
            __delay_ms(300);            
        }
    }
    if (INTCON3bits.INT1IF==1)
    {
        while (PORTDbits.RD4==1)//inicar funcion
        {
            Temp ();
        }
        if (PORTBbits.RB2==0)
        {
            PORTDbits.RD7=0;
            INTCON3bits.INT1IF=0;            
        }
        else
        {
            PORTDbits.RD7=1;
        }
    }
}
void __interrupt (low_priority) ISR_RB(void)
{
    if (INTCON3bits.INT2IF==1)//iniciar modo de pare
    {
        while (PORTBbits.RB3==1)
        {
            PORTDbits.RD5=1;
        }
        if (PORTBbits.RB3==0)
        {
            INTCON3bits.INT2IF=0;
            PORTDbits.RD5=0;
        }
    }
    if (INTCONbits.RBIF==1)
    {
        cont1++;//incluir numero
        if (PORTCbits.RC0==0)//teclado matricial
        {
            if (PORTBbits.RB4==0) {num=1;}
            if (PORTBbits.RB5==0) {num=4;}
            if (PORTBbits.RB6==0) {num=7;}
            if (PORTBbits.RB7==0) {opc='*';}
        }
        if (PORTCbits.RC1==0)
        {
            if (PORTBbits.RB4==0) {num=2;}
            if (PORTBbits.RB5==0) {num=5;}
            if (PORTBbits.RB6==0) {num=8;}
            if (PORTBbits.RB7==0) {num=0;}
        }
        if (PORTCbits.RC2==0)
        {
            if (PORTBbits.RB4==0) {num=3;}
            if (PORTBbits.RB5==0) {num=6;}
            if (PORTBbits.RB6==0) {num=9;}
            if (PORTBbits.RB7==0) {PORTAbits.RA5=1;}
        }
        while (PORTBbits.RB4==0||PORTBbits.RB5==0||PORTBbits.RB6==0||PORTBbits.RB7==0);
        INTCONbits.RBIF=0;
    }
}
// *Empieza, #pausa, led de encendido mientras funciona, más de 60° otro led rojo se enciende.
// Si se pulsa un botón en otro lado entra en mantenimiento, displays 1-9, leds intermitentes 3 veces.