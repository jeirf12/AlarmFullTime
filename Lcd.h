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

#define LCD_Data LATC              /* Define LCD data port direction */
#define LCD_Port TRISC           /* Define LCD command port direction register */
#define EN LATC2                            /* Define Enable signal pin */
#define RS LATC1    

void LCD_Init();
void LCD_Command(unsigned char);
void LCD_Char(unsigned char x);
void LCD_String(const char *);
void delayms(unsigned int);
void LCD_String_xy(char ,char ,const char*);
void LCD_Clear();
    
#ifdef __cplusplus
}
#endif /* end macro __cplusplus */

#endif /* end macro CONFIG_H */
