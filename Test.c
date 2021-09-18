/* 
 * File:   Test.c
 * Author: jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on 27 April 2021, 15:44
 */

#include <xc.h>
#include "Config.h"
#include "Pinout.h"
#include "Lcd.h"

/*
 * Start program
 */
int main(int argc, char** argv) {
    OSCCON = 0x72;
    CNF_LED_RED = OUTPUT;
    CNF_SENSOR = OUTPUT;
    while(1){
        LED_RED = ON;
        MSdelay(500);
        LED_RED = OFF;
        MSdelay(500);
    }
}

