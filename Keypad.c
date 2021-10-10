/* 
 * @File   Keypad.c
 * @Author jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on 27 April 2021, 15:44
 */

#include <xc.h>
#include "Keypad.h"


/**
 * @brief get keypad key
 * @return key keypad
 */
unsigned char keyfind(void){
    Direction_Port_A = 0x0f;
    Direction_Port_C = 0xf0;         
    write_port = 0xf0;              /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/  
    
    do{
        do{
            col_loc = read_port & 0x0f; /*mask port with f0 and copy it to col_loc variable*/   
        }while(col_loc != 0x0f);          /*Check initially at the start there is any key pressed*/ 
        delayms(20);
        col_loc = read_port & 0x0f;    /*mask port with f0 and copy it to col_loc variable*/  
    }while(col_loc == 0x0f); 
    
    while(1){
        if(waitKeyRow(0xf1, 0)) break;
        if(waitKeyRow(0xf2, 1)) break;
        if(waitKeyRow(0xf4, 2)) break;
    }
    delayms(100);
    if(col_loc == 0x0e) return keypad[0][*rowloc];      /*Return key pressed value to calling function*/            
    else if(col_loc == 0x0d) return keypad[1][*rowloc];       /*Return key pressed value to calling function*/  
    else if(col_loc == 0x0b) return keypad[2][*rowloc];
    else if(col_loc == 0x07) return keypad[3][*rowloc];       /*Return key pressed value to calling function*/
    return 'e';
}

unsigned char waitKeyRow(unsigned char port, unsigned char row){
    write_port = port;                  /*make Row0(D3) Gnd and keep other row(D0-D2) high*/
    temp_col = read_port & 0x0f;         /*Read Status of PORT for finding Row*/
    if(temp_col == 0x0f){              
        *rowloc = row;
        return 1;
    }
    return 0;
}