
#define RS      LATEbits.LATE0     //Se debe de definir el Pin Usado para RS
#define EN      LATEbits.LATE1       //Se debe de definir el pin Usado para E
#define TRISRS  TRISEbits.TRISE0    //Se define el Tris para el RS Para poderlo configurar como Salida
#define TRISEN  TRISEbits.TRISE1    //Se define el Tris para el E Para poderlo configurar como Salida
#define PUERTOTRS TRISC             // Se define el TRIS del puerto que se usa como interfaz en este caso el Puerto C
#define PUERTO LATC                 // Se define El LAT del puerto que se usa como interfaz en este caso el C
void lcd_init();
void lcd_control(char);
void lcd_dato(char);
void lcd_clear_display();
void lcd_cursor_home();
void lcd_print(char*);
void lcd_goto(int, int);
void lcd_time_control(void);

/*
 * Configuracion de Puertos
 * Iniciliaza el los puertos requeridos para el LCD
 * Ademas lo inicializa a 4 Bits
 */

void lcd_init() {
    
    TRISRS = 0; //Configuramos el Pin RS como salida
    TRISEN = 0; //Configuramos el Pin E como salida
    PUERTOTRS = 0b00001111; //Configuramos El nibble mas significativo como Salidas (Bus de 4 Bits))
    RS = 0; //Aseguramos RS en 0            
    EN = 0; //Aseguramos E en 0
    PUERTO = 0; //Aseguramos el Puerto de datos en 0
    /*
     * Configuracion del control del LCD
     */
    __delay_ms(50); // Tiempo de espera a que se estabilicen los puertos
    lcd_control(0x02); //Asegura el Cursos del LCD Al inicio (Home)
    lcd_control(0x28); //Configura el LCD a 4 Bits, 2 Lineas Y Fuente de 5*8; Lineas Esto se llama el function set
    lcd_control(0x0C); //LCD Prendido, Cursor Apagado, Destello Cursor apagado; Esto se Llama Diplay on/off Control
    lcd_control(0x06); //No rota el mensaje Y se incrementa el contador de direccion. Esto se Llama Entry Mode Set
}

/*
 * Esta rutina se encarga de tomar un dato y ponerlo en el puerto de datos
 * teniendo en cuenta que es a 4 bits, por lo tanto tiene que desplazar los bits
 * primer se envia los 4 bits mas significativo y luego se envia los 4 bits  menos significativo
 */
void lcd_control(char dato) {
    RS = 0;
    PUERTO = dato & 0xF0;
    lcd_time_control();
    PUERTO = ((dato & 0x0F) << 4);
    lcd_time_control();
    __delay_ms(2);
}

/*
 * Está rutina se encarga de tomar un dato y ponerlo sobre el puerto de datos
 * especificamente para escribir un caracter sobre el LCD
 * 
 */
void lcd_dato(char dato) {
    RS = 1;
    PUERTO = dato & 0xF0;
    lcd_time_control();
    PUERTO = ((dato & 0x0F) << 4);
    lcd_time_control();
    __delay_us(50);
}

/*
 * Rutina encargada de limpiar el LCD
 */
void lcd_clear_display() {
    lcd_control(0x01);
}

/*
 * El puntero regresa al inicio sin modificar los datos del LCD
 */
void lcd_cursor_home() {
    lcd_control(0x02);
}

/*
 * Imprime una cadena de caractres en el LCD
 */
void lcd_print(char *dato) {
    while (*dato) // Mientras no sea Null
    {
        lcd_dato(*dato); // Envio el dato al LCD
        dato++; // Incrementa el buffer de dato
    }
}
/*
 * Pone el puntero en la posicion deseada
 */
void lcd_goto(int x, int y) {
    char posicion;
    switch (y) {
        case 1: posicion = 0x80 + x;
            break;
        case 2: posicion = 0xC0 + x;
            break;
        default: posicion = 0x80 + x;
            break;
    }
    lcd_control(posicion);
}
/*
 * Genera un Pulso de control Ese pulso es un pulso de E a 1 milisegundos
 */
void lcd_time_control(void) {
    EN = 1;
    __delay_us(5);
    EN = 0;
    __delay_us(5);
}