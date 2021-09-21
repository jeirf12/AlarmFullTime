/* 
 * @File   Lcd.c
 * @Author jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on 27 April 2021, 15:44
 */

#include <xc.h>
#include "Lcd.h"

/**
 * delay in controller
 * @param value milliseconds to delay
 */
void delayms(unsigned int value){
    while(value--){
      __delay_ms(1);           /*This count Provide delay of 1 ms for 8MHz Frequency */
    }
}

/**
 * LCD command write function
 * @param cmd send command execute in hexadecimal o binary
 */
void LCD_Command(unsigned char cmd )
{
	LCD_Data = (LCD_Data & 0x0f) |(0xF0 & cmd);   /*Send higher nibble of command first to PORT*/ 
	RS = 0;                                 /*Command Register is selected i.e.RS=0*/ 
	EN = 1;                                 /*High-to-low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
	delayms(1);
    LCD_Data = (LCD_Data & 0x0f) | (cmd<<4);      /*Send lower nibble of command to PORT */
	EN = 1;
	NOP();
	EN = 0;
	delayms(3);
}

/**
 * LCD data write function
 * @param char_data chain write
 */
void LCD_Char(unsigned char dat)
{
	LCD_Data = (LCD_Data & 0x0f) | (0xF0 & dat);   /*Send higher nibble of data first to PORT*/
	RS = 1;                                  /*Data Register is selected*/
	EN = 1;                                  /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	delayms(1);
    LCD_Data = (LCD_Data & 0x0f) | (dat<<4);               /*Send lower nibble of data to PORT*/
	EN = 1;                         /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	delayms(3);
}

/**
 * LCD Initialize function
 */
void LCD_Init(void){
  LCD_Port = 0;                          /* Make LCD data port direction as o/p */             
  delayms(15);                               /* LCD power up time to get things ready, it should always >15ms */
  LCD_Command(0x02);
  LCD_Command(0x28);
  LCD_Command(0x01);                         /* Clear LCD command */
  LCD_Command(0x0C);                         /* Display ON, Cursor OFF command */
  LCD_Command(0x06);                         /* Auto Increment cursor */ 
}

/**
 * Send string to LCD function
 * @param str chain write
 */
void LCD_String(const char *str){
  while((*str)!=0){                          /* Send each char of string till the NULL */
    LCD_Char(*str);                          /* Call LCD data write */
    str++;
  }
}

/**
 * Send string to LCD function
 * @param row send row show
 * @param pos send column show
 * @param str send chain show
 */
void LCD_String_xy(char row, char pos,const char *str){
  char location=0;
  if(row<=1){
    location = (0x80) | ((pos) & 0x0f);      /*Print message on 1st row and desired location*/
    LCD_Command(location);
  }
  else{
    location = (0xC0) | ((pos) & 0x0f);      /*Print message on 2nd row and desired location*/
    LCD_Command(location);    
  }  
  LCD_String(str);                           /* Call LCD string function */
}

/**
 * LCD clear function
 */
void LCD_Clear(void){
  LCD_Command(0x01);                         /* Clear LCD command */
}
