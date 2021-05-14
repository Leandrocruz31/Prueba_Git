# 1 "../../../../Desktop/lcd.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.45/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "../../../../Desktop/lcd.c" 2
# 75 "../../../../Desktop/lcd.c"
    typedef struct
    {
    BOOLEAN enable;
    BOOLEAN rs;
    BOOLEAN rw;
    BOOLEAN unused;
    int data : 4;



    } LCD_PIN_MAP;
# 185 "../../../../Desktop/lcd.c"
    BYTE const LCD_INIT_STRING[4] = {0×20 | (2 << 2), 0xc, 1, 6};



    BYTE lcd_read_nibble(void);

    BYTE lcd_read_byte(void)
    {
    BYTE low,high;
# 204 "../../../../Desktop/lcd.c"
    lcdtris.data = 0xF;



    lcdlat.rw=1;
    delay_cycles(1);
    lcdlat.enable=1;
    delay_cycles(1);
    high = lcd_read_nibble();

    lcdlat.enable=0;
    delay_cycles(1);
    lcdlat.enable=1;
    delay_us(1);
    low = lcd_read_nibble();

    lcdlat.enable=0;
# 231 "../../../../Desktop/lcd.c"
    lcdtris.data = 0×0;



    return( (high<<4) | low);
    }

    BYTE lcd_read_nibble(void)
    {
# 251 "../../../../Desktop/lcd.c"
    return(lcd.data);

    }

    void lcd_send_nibble(BYTE n)
    {







    lcdlat.data = n;


    delay_cycles(1);
    lcdlat.enable=1;
    delay_us(2);
    lcdlat.enable=0;
    }

    void lcd_send_byte(BYTE address, BYTE n)
    {



    lcdtris.enable=0;
    lcdtris.rs=0;
    lcdtris.rw=0;


    lcdlat.rs=0;
    while ( bit_test(lcd_read_byte(),7) ) ;
    lcdlat.rs=address;
    delay_cycles(1);
    lcdlat.rw=0;
    delay_cycles(1);
    lcdlat.enable=0;
    lcd_send_nibble(n >> 4);
    lcd_send_nibble(n & 0xf);
    }





    void lcd_init(void)
    {
    BYTE i;
# 311 "../../../../Desktop/lcd.c"
    lcdtris.data = 0×0;

    lcdtris.enable=0;
    lcdtris.rs=0;
    lcdtris.rw=0;


    lcdlat.rs=0;
    lcdlat.rw=0;
    lcdlat.enable=0;

    delay_ms(15);
    for(i=1;i<=3;++i)
    {
    lcd_send_nibble(3);
    delay_ms(5);
    }

    lcd_send_nibble(2);
    for(i=0;i<=3;++i)
    lcd_send_byte(0,LCD_INIT_STRING[i]);





    }

    void lcd_gotoxy(BYTE x, BYTE y)
    {
    BYTE address;

    if(y!=1)
    address=0×40;
    else
    address=0;

    address+=x-1;
    lcd_send_byte(0,0×80|address);





    }

    void lcd_putc(char c)
    {
    switch (c)
    {
    case ‘\a’ : lcd_gotoxy(1,1); break;

    case ‘\f’ : lcd_send_byte(0,1);
    delay_ms(2);




    break;
# 381 "../../../../Desktop/lcd.c"
    case ‘\n’ : lcd_gotoxy(1,2); break;


    case ‘\b’ : lcd_send_byte(0,0×10); break;
# 395 "../../../../Desktop/lcd.c"
    default : lcd_send_byte(1,c); break;

    }
    }

    char lcd_getc(BYTE x, BYTE y)
    {
    char value;

    lcd_gotoxy(x,y);
    while ( bit_test(lcd_read_byte(),7) );
    lcdlat.rs=1;
    value = lcd_read_byte();
    lcdlat.rs=0;

    return(value);
    }
