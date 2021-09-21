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
 *  find key 
 * @return 
 */
char keypad_getkey(void){

  char letras[4][3]={  {'1','2','3'},
                       {'4','5','6'},
                       {'7','8','9'},
                       {'c','0','o'}};
  int  i=0;
  char valor=0;

  for(i=0;i<4;i++){
    if(i==0){
      FILAS = (1<<COL3)|(1<<COL2)|(1<<COL1)|(1<<ROW4)|(1<<ROW3)|(1<<ROW2)|(0<<ROW1);
      delayms(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[0][0];}   //1
      while (!(COLUMNAS & (1<<COL2))){valor=letras[0][1];}   //2
      while (!(COLUMNAS & (1<<COL3))){valor=letras[0][2];}   //3
    }

    if(i==1){
      FILAS = (1<<COL3)|(1<<COL2)|(1<<COL1)|(1<<ROW4)|(1<<ROW3)|(0<<ROW2)|(1<<ROW1);
      delayms(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[1][0];}   //4
      while (!(COLUMNAS & (1<<COL2))){valor=letras[1][1];}   //5
      while (!(COLUMNAS & (1<<COL3))){valor=letras[1][2];}   //6
    }

    if(i==2){
      FILAS = (1<<COL3)|(1<<COL2)|(1<<COL1)|(1<<ROW4)|(0<<ROW3)|(1<<ROW2)|(1<<ROW1);
      delayms(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[2][0];}   //7
      while (!(COLUMNAS & (1<<COL2))){valor=letras[2][1];}   //8
      while (!(COLUMNAS & (1<<COL3))){valor=letras[2][2];}   //9
    }

    if(i==3){
      FILAS = (1<<COL3)|(1<<COL2)|(1<<COL1)|(0<<ROW4)|(1<<ROW3)|(1<<ROW2)|(1<<ROW1);
      delayms(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[3][0];}   //c
      while (!(COLUMNAS & (1<<COL2))){valor=letras[3][1];}   //0
      while (!(COLUMNAS & (1<<COL3))){valor=letras[3][2];}   //ok
    }
  }
  return valor;
}

/**
 * Scan the Keypad
 * @return 
 */
short keypad_read(){
  LATDbits.LATD3 = 1;
  delayms(10);
  if(PORTDbits.RD0 == 1){
    while(PORTDbits.RD0 == 1);
    return 3;
  }else if(PORTDbits.RD1 == 1){
    while(PORTDbits.RD1 == 1);
    return 2;
  }else if(PORTDbits.RD2 == 1){
    while(PORTDbits.RD2 == 1);
    return 1;
  }
  LATDbits.LATD3 = 0;
  LATDbits.LATD4 = 1;
  delayms(10);
  if(PORTDbits.RD0 == 1){
    while(PORTDbits.RD0 == 1);
    return 6;
  }else if(PORTDbits.RD1 == 1){
    while(PORTDbits.RD1 == 1);
    return 5;
  }else if(PORTDbits.RD2 == 1){
    while(PORTDbits.RD2 == 1);
    return 4;
  }
  LATDbits.LATD4 = 0;
  LATDbits.LATD5 = 1;
  delayms(10);
  if(PORTDbits.RD0 == 1){
    while(PORTDbits.RD0 == 1);
    return 9;
  }else if(PORTDbits.RD1 == 1){
    while(PORTDbits.RD1 == 1);
    return 8;
  }else if(PORTDbits.RD2 == 1){
    while(PORTDbits.RD2 == 1);
    return 7;
  } 
  LATDbits.LATD5 = 0;
  LATDbits.LATD6 = 1;
  delayms(10);
  if(PORTDbits.RD0 == 1){
    while(PORTDbits.RD0 == 1);
    return 12;
  }else if(PORTDbits.RD1 == 1){
    while(PORTDbits.RD1 == 1);
    return 11;
  }else if(PORTDbits.RD2 == 1){
    while(PORTDbits.RD2 == 1);
    return 10;
  }  
  LATDbits.LATD6 = 0;
  return 0;
}

/**
 * Convert keypad value to character
 * @param a
 * @return 
 */
char decode_character(short a){
  switch(a){
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 11: return '0';
  }
}
