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
  PTECLADO &= ~(1<<ROW1) & ~(1<<ROW2) & ~(1<<ROW3) & ~(1<<ROW4);   //   FILAS  - SALIDA
  PTECLADO |= (1<<COL1) | (1<<COL2) | (1<<COL3);       // COLUMNAS - ENTRADA
  //RDPU = 0;
  //INTCON2bits.RBPU = 0;                                        //   PORTB  pull-ups are enabled by individual port latch values 
}

/**
 * @brief get keypad key
 * @return key keypad
 */
//unsigned char keyfind(void){
//    Direction_Port = 0xf0;              /*TRISB = 0B 1111 0000*/
//    write_port = 0xf0;              /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/   
//    
//    do{
//        do{
//            col_loc = read_port & 0xf0; /*mask port with f0 and copy it to col_loc variable*/   
//        }while(col_loc != 0xf0);          /*Check initially at the start there is any key pressed*/ 
//        col_loc = read_port & 0xf0;    /*mask port with f0 and copy it to col_loc variable*/  
//    }while(col_loc != 0xf0);  
//    delayms(50);
//    do{ 
//        do{     
//            col_loc = read_port & 0xf0;
//        }while(col_loc == 0xf0);      /*Wait for key press*/
//        col_loc = read_port & 0xf0;
//    }while(col_loc == 0xf0);          /*Wait for key press*/   
//    delayms(20);
//    
//    while(1){
//        delayms(20);
//        if(waitKeyRow(0xfe, 0)) break;
//        if(waitKeyRow(0xfd, 1)) break;
//        if(waitKeyRow(0xfb, 2)) break;
//        if(waitKeyRow(0xf7, 3)) break;
//    }
//    while(1){
//        if(col_loc == 0xe0) return letras[*rowloc][0];      /*Return key pressed value to calling function*/            
//        else if(col_loc == 0xd0) return letras[*rowloc][1];       /*Return key pressed value to calling function*/   
//        else if(col_loc == 0xb0) return letras[*rowloc][2];       /*Return key pressed value to calling function*/
//    }
//}

unsigned char keyfind(void){
    unsigned char key;
    setColumnHigh();
    delayms(10);
    setColumn1();
    delayms(10);
    if (ROW1 == 0) {
        //return key1();
        key = '1';
    }
    if (ROW2 == 0) {
//        return key4();
        key = '4';
    }
    if (ROW3 == 0) {
//        return key7();
        key = '7';
    }
    delayms(10);
    setColumn2();
    delayms(10);
    if (ROW1 == 0) {
//        return key2();
        key = '2';
    }
    if (ROW2 == 0) {
//        return key5();
        key = '5';
    }
    if (ROW3 == 0) {
//        return key8();
        key = '8';
    }
    if (ROW4 == 0) {
//        return key0();
        key = '0';
    }
    delayms(10);
    setColumn3();
    delayms(10);
    if (ROW1 == 0) {
//        return key3();
        key = '3';
    }
    if (ROW2 == 0) {
//        return key6();
        key = '6';
    }
    if (ROW3 == 0) {
//        return key9();
        key = '9';
    }
    return key;
}

unsigned char setColumnHigh(){
    COL1 = 1;
    COL2 = 1;
    COL3 = 1;
}
unsigned char setColumn1(){
    COL1 = 0;
    COL2 = 1;
    COL3 = 1;
}
unsigned char setColumn2(){
    COL1 = 1;
    COL2 = 0;
    COL3 = 1;
}
unsigned char setColumn3(){
    COL1 = 1;
    COL2 = 1;
    COL3 = 0;
}
unsigned char key1(){
//    Direction_Port = 0xF9;
    return '1';
}
unsigned char key2(){
//    Direction_Port = 0xA4;
    return '2';
}
unsigned char key3(){
//    Direction_Port = 0xB0;
    return '3';
}
unsigned char key4(){
//    Direction_Port = 0x99;
    return '4';
}
unsigned char key5(){
//    Direction_Port = 0x92;
    return '5';
}
unsigned char key6(){
//    Direction_Port = 0x82;
    return '6';
}
unsigned char key7(){
//    Direction_Port = 0xF8;
    return '7';
}
unsigned char key8(){
//    Direction_Port = 0x80;
    return '8';
}
unsigned char key9(){
//    Direction_Port = 0x90;
    return '9';
}
unsigned char key0(){
//    Direction_Port = 0xC0;
    return '0';
}
unsigned char keyNope(){
//    Direction_Port = 0x3F;
    return '0';
}
//void keyC(){
//    Direction_Port = 0xf9;
//}
//void keyOk(){
//    Direction_Port = 0xf9;
//}

//unsigned char waitKeyRow(unsigned char port, unsigned char row){
//    write_port = port;                  /*make Row0(D3) Gnd and keep other row(D0-D2) high*/
//    col_loc = 0xf0 & read_port;         /*Read Status of PORT for finding Row*/
//    if(col_loc != 0xf0){              
//        *rowloc = row;
//        return 1;
//    }
//    return 0;
//}