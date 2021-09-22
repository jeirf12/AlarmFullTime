/* 
 * @File   Keypad.h
 * @Author jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on 14 September 2021, 16:37
 */

#include <pic18f4550.h>
#include "Lcd.h"
#include <stdbool.h>

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

#define PTECLADO  TRISB
#define FILAS     LATB
#define COLUMNAS  PORTB

#define write_port LATB             /* latch register to write data on port */
#define read_port PORTB             /* PORT register to read data of port */
#define Direction_Port TRISB


unsigned char col_loc, *rowloc, temp_col, port;
char letras[4][3]={  {'1','2','3'},
                       {'4','5','6'},
                       {'7','8','9'},
                       {'c','0','o'}};

unsigned char password[5] = "2021";
unsigned char pass_user[5];
unsigned char idx = 0;

/**
 * @brief start keypad
 */
void keypad_init (void);

/**
 * @brief get keypad key
 * @return key keypad
 */
unsigned char keyfind(void);        /* function to find pressed key */ 

/**
 * @brief wait key while they press it
 * @param port
 * @param row
 * @return true or false key row selected
 */
bool waitKeyRow(unsigned char port, unsigned char row);

#ifdef __cplusplus
}
#endif /* end macro __cplusplus */

#endif /* end macro CONFIG_H */
