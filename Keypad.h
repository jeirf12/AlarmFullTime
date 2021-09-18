/* 
 * File:   Keypad.h
 * Author: jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on 14 September 2021, 16:37
 */

#include <pic18f4550.h>
#include "Lcd.h"

#ifndef KEYPAD_H
#define KEYPAD_H

#ifdef __cplusplus
extern "C" {
#endif /* end macro __cplusplus */

#define _XTAL_FREQ  8000000L

#define PB6     6
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0

/* FILAS-SALIDAS */
#define ROW1   PB0
#define ROW2   PB1
#define ROW3   PB2
#define ROW4   PB3

/* COLUMNAS-ENTRADAS */
#define COL1   PB4
#define COL2   PB5
#define COL3   PB6

#define PTECLADO  TRISD
#define FILAS     LATD
#define COLUMNAS  PORTD

#define write_port LATD             /* latch register to write data on port */
#define read_port PORTD             /* PORT register to read data of port */
#define Direction_Port TRISD

void keypad_init (void);
char keypad_getkey(void);
unsigned char keypad_findKey();     /* function to find pressed key */

short keypad_read();                //Scan the Keypad
char decode_character(short a);     //Convert keypad value to character

#ifdef __cplusplus
}
#endif /* end macro __cplusplus */

#endif /* end macro CONFIG_H */
