/* 
 * File:   Lcd.h
 * Author: jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on 14 September 2021, 16:37
 */

#include <pic18f4550.h>

#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif /* end macro __cplusplus */

#define LCD_Data_Dir TRISD0              /* Define LCD data port direction */
#define LCD_Command_Dir TRISE           /* Define LCD command port direction register */
#define LCD_Data_Port LATD0              /* Define LCD data port */
#define LCD_Command_Port LATE           /* Define LCD data port */
#define EN LATE2                            /* Define Enable signal pin */
#define RW LATD2                            /* Define Read/Write signal pin */
#define RS LATE1    

void LCD_Init();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void MSdelay(unsigned int );
void LCD_String_xy(char ,char ,const char*);
void LCD_Custom_Char(unsigned char loc,unsigned char *msg);
void LCD_Clear();
    
#ifdef __cplusplus
}
#endif /* end macro __cplusplus */

#endif /* end macro CONFIG_H */
