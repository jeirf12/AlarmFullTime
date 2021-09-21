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
    OSCCON = 0x72;
    CNF_LED_GREEN = OUTPUT;
    /* CNF_SENSOR = OUTPUT; */
    while(1){
        LED_GREEN = ON;
        delayms(500);
        LED_GREEN = OFF;
        delayms(500);
    }
    LCD_Init();
    LCD_Clear();
    LCD_String_xy(2, 0, "key");
    keypad_init();
}

