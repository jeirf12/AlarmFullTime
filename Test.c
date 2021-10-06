/*
 * @File   Test.c
 * @Author jhonfer <jruizf@unicauca.edu.co>
 * 
 * @brief main program   
 *
 * Created on 27 April 2021, 15:44
 */
#include <xc.h>
#include<string.h>
#include "Config.h"
#include "Pinout.h"
#include "Lcd.h"
#include "Keypad.h"
#include "MemoryEEPROM.h"

/**
 * Start program
 * @return 
 */
int main(){
//    initMemory();
//    writeData(0, 2);
//    writeData(1, 0);
//    writeData(2, 2);
//    writeData(3, 1);
//    while(1){
//        LATD = readData(3);
//    }
    unsigned char key;
    OSCCON = 0x72;
    LCD_Init();
    LCD_String_xy(1, 0, "Press Password");
    LCD_Command(0xC0);
    while(1){
//        do{
            key = keyfind(); /* find a pressed key */
            LCD_Char(key); /* display pressed key on LCD16x2 */
//            if(key == 'o'){
//                if(strcmp(&password, &pass_user) != 0){
//                    LCD_Clear();
//                    LCD_String_xy(1, 0, "Press Password");
//                    LCD_Command(0xC0);
//                    idx = -1;
//                    memset(pass_user, 0, 5);
//                }else break;
//            }else pass_user[idx] = key;
//            idx++;
//        }while(1);
//        LCD_Clear();
//        LCD_String("**Welcome Home**");
    }
}