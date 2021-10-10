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

#define PA6     6
#define PA5     5
#define PA4     4
#define PA3     3
#define PA2     2
#define PA1     1
#define PA0     0

/* ROW-OUTPUT */
#define ROW1   PA0
#define ROW2   PA1
#define ROW3   PA2
#define ROW4   PA3

/* COLUMNS-INPUT */
#define COL1   PA4
#define COL2   PA5
#define COL3   PA6

#define PTECLADO  TRISA
#define FILAS     LATA
#define COLUMNAS  PORTA

#define write_port LATC             /* latch register to write data on port */
#define read_port PORTA             /* PORT register to read data of port */
#define Direction_Port_A TRISA
#define Direction_Port_C TRISC


unsigned char col_loc, *rowloc, temp_col;
unsigned char keypad[4][3]= {'1','2','3',
                             '4','5','6',
                             '7','8','9',
                             'c','0','o'};

unsigned char password[5] = "2021";
unsigned char pass_user[5];
unsigned char idx = 0;

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
unsigned char waitKeyRow(unsigned char port, unsigned char row);

#ifdef __cplusplus
}
#endif /* end macro __cplusplus */

#endif /* end macro CONFIG_H */
