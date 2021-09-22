/* 
 * @File   Keypad.c
 * @Author jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on 27 April 2021, 15:44
 */

#include <xc.h>
#include "Keypad.h"

/**
 * start keypad
 */
void keypad_init(void){
  PTECLADO &= ~(1<<PB0) & ~(1<<PB1) & ~(1<<PB2) & ~(1<<PB3);   //   FILAS  - SALIDA
  PTECLADO |= (1<<PB4) | (1<<PB5) | (1<<PB6);       // COLUMNAS - ENTRADA
  INTCON2bits.RBPU = 0;                                        //   PORTB  pull-ups are enabled by individual port latch values 
}

/**
 * @brief get keypad key
 * @return key keypad
 */
unsigned char keyfind(void){      
    Direction_Port = 0xf0;              /*TRISB = 0B 1111 0000*/
    write_port = 0xf0;              /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/
    do{
        do{
            col_loc = read_port & 0xf0; /*mask port with f0 and copy it to col_loc variable*/   
        }while(col_loc!=0xf0);          /*Check initially at the start there is any key pressed*/ 
        col_loc = read_port & 0xf0;    /*mask port with f0 and copy it to col_loc variable*/  
    }while(col_loc!=0xf0);  
    delayms(50);
    write_port = 0xf0;              /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/
    do{ 
        do{     
            col_loc = read_port & 0xf0;
        }while(col_loc==0xf0);      /*Wait for key press*/
        col_loc = read_port & 0xf0;
    }while(col_loc==0xf0);          /*Wait for key press*/
               
    delayms(20);
    col_loc = read_port & 0xf0;           
    
    while(1){
        if(waitKeyRow(0xfe, 0)) break;
        if(waitKeyRow(0xfd, 1)) break;
        if(waitKeyRow(0xfb, 2)) break;
        if(waitKeyRow(0xf7, 3)) break;
    }
    while(1){
        if(col_loc==0xe0) return letras[*rowloc][0];      /*Return key pressed value to calling function*/            
        else if(col_loc==0xd0) return letras[*rowloc][1];       /*Return key pressed value to calling function*/   
        else if(col_loc==0xb0) return letras[*rowloc][2];       /*Return key pressed value to calling function*/
    }  
    delayms(300);
}

bool waitKeyRow(unsigned char port, unsigned char row){
    write_port = port;                  /*make Row0(D3) Gnd and keep other row(D0-D2) high*/
    col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
    temp_col=col_loc;
    if(col_loc!=0xf0){
        *rowloc = row;                       /*If condition satisfied get Row no. of key pressed*/
        while(temp_col!=0xf0) {         /*Wait for key to release*/
            temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
        }
        return true;
    }
    return false;
}
