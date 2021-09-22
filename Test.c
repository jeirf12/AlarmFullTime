/*
 * @File   Test.c
 * @Author jhonfer <jruizf@unicauca.edu.co>
 * 
 * @brief main program   
 *
 * Created on 27 April 2021, 15:44
 */
#include <xc.h>
#include "Config.h"
#include "Pinout.h"
#include "Lcd.h"
#include "Keypad.h"

/**
 * Start program
 * @return 
 */
int main() {
    char key;
    OSCCON = 0x72;
    LCD_Init();
    LCD_String_xy(1, 0, "Press Password");
    LCD_Command(0xC0);
    keypad_init();
    while(1){
        do{             
            key = keyfind();            /* find a pressed key */
            LCD_Char('*');                  /* display pressed key on LCD16x2 */
            if(password[idx] == key) {
               pass_user[idx++];
            }
            if(key == 'o' && idx < 4){
                LCD_Clear();
                LCD_String_xy(1, 0, "Press Password");
                LCD_Command(0xC0);
            }
        }while(idx < 5);
        LCD_Clear(); 
        LCD_String("Welcome To House");     
    }
}