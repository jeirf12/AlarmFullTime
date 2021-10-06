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
#define ROW1   LATA0
#define ROW2   LATA1
#define ROW3   LATA2
#define ROW4   LATA3

/* COLUMNS-INPUT */
#define COL1   RA4
#define COL2   RA5
#define COL3   RA6

#define PTECLADO  TRISA
#define FILAS     LATA
#define COLUMNAS  PORTA

#define write_port LATA             /* latch register to write data on port */
#define read_port PORTA             /* PORT register to read data of port */
#define Direction_Port TRISA


unsigned char col_loc, *rowloc, temp_col, port;
char letras[4][3] = {{'1','2','3'},
                    {'4','5','6'},
                    {'7','8','9'},
                    {'c','0','o'}};

unsigned char password[5] = "2021";
unsigned char pass_user[5];
unsigned char idx = 0;

/**
 * @brief start keypad
 */
void keypad_init(void);

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

unsigned char setColumnHigh();
unsigned char setColumn1();
unsigned char setColumn2();
unsigned char setColumn3();
unsigned char key1();
unsigned char key2();
unsigned char key3();
unsigned char key4();
unsigned char key5();
unsigned char key6();
unsigned char key7();
unsigned char key8();
unsigned char key9();
unsigned char key0();

#ifdef __cplusplus
}
#endif /* end macro __cplusplus */

#endif /* end macro CONFIG_H */
