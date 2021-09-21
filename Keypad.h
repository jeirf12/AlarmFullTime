/* 
 * @File   Keypad.h
 * @Author jhonfer <jruizf@unicauca.edu.co>
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

#define PB6     6
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0

/* ROW-OUTPUT */
#define ROW1   PB0
#define ROW2   PB1
#define ROW3   PB2
#define ROW4   PB3

/* COLUMNS-INPUT */
#define COL1   PB4
#define COL2   PB5
#define COL3   PB6

#define PTECLADO  TRISD
#define FILAS     LATD
#define COLUMNAS  PORTD

#define write_port LATD             /* latch register to write data on port */
#define read_port PORTD             /* PORT register to read data of port */
#define Direction_Port TRISD

/**
 * @brief start keypad
 */
void keypad_init (void);

/**
 * @brief get keypad key
 * @return key keypad
 */
char keypad_getkey(void);
//unsigned char keypad_findKey();     /* function to find pressed key */

/**
 * @brief scan key in keypad
 * @return key value
 */
short keypad_read();                //Scan the Keypad

/**
 * @brief convert key value to character name
 * @param a send keypad value
 * @return key name
 */
char decode_character(short a);     //Convert keypad value to character

#ifdef __cplusplus
}
#endif /* end macro __cplusplus */

#endif /* end macro CONFIG_H */
