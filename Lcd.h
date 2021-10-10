/* 
 * @File   Lcd.h
 * @Author jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on 14 September 2021, 16:37
 */

#include <pic18f4550.h>
#include "Config.h"

#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif /* end macro __cplusplus */

#define LCD_Data LATD              /* Define LCD data port direction */
#define LCD_Direction TRISD           /* Define LCD command port direction register */
#define RW LATD1
#define EN LATD2                            /* Define Enable signal pin */
#define RS LATD0

unsigned char doorOpen[] = {0x1F, 0x11, 0x11, 0x13, 0x13, 0x11, 0x11, 0x1F};
unsigned char doorClose[] = {0x1F, 0x1F, 0x1F, 0x1D, 0x1D, 0x1F, 0x1F, 0x1F};
unsigned char windowsOpen[] = {0x1F, 0x15, 0x15, 0x1F, 0x1F, 0x15, 0x15, 0x1F};
unsigned char windowsClose[] = {0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x1B, 0x1B, 0x1B};
    
void LCD_Init();
void LCD_Command(unsigned char);
void LCD_Char(unsigned char x);
void LCD_String(const char *);
void delayms(unsigned int);
void LCD_String_xy(char, char, const char*);
void LCD_Clear();
void LCD_Custom_Char(unsigned char loc, unsigned char *msg);
    
#ifdef __cplusplus
}
#endif /* end macro __cplusplus */

#endif /* end macro CONFIG_H */
