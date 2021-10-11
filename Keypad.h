/* 
 * @File   Keypad.h
 * @Author jhonfer <jruizf@unicauca.edu.co>
 * @Author: Yaquelin Gomez
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