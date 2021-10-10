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
#include <stdio.h>
#include "Config.h"
#include "Pinout.h"
#include "Lcd.h"
#include "Keypad.h"
#include "MemoryEEPROM.h"
#include "I2C.h"
#include "Rtc.h"

void sensorMotion();
void showCustomCaracter(unsigned char pos, unsigned char *msg);
void callRtc();
void timerInit();
void intInit();

void __interrupt() ISR_TIMER_0(void);
//void __interrupt() INT_EXT_0(void);

/**
 * Start program
 * @return 
 */
int main() {
    ADCON1 = 0x0f;
    OSCCON = 0x72;
    //CMCON = 0x07;
    unsigned char chain, key;
    unsigned char hora [20];
    initMemory();
    writeMemoryString(0, "2021");
    //chain = ReadMemoryString(0,3);
    I2C_Init();
    LCD_Init();
    //intInit();
    LCD_String_xy(1, 0, "Press Password");
    LCD_Command(0xC0);
    while (1) {
        do {
            key = keyfind(); /* find a pressed key */
            LCD_Char('*'); /* display pressed key on LCD16x2 */
            if (key == 'o') {
                if (strcmp(&password, &pass_user) != 0) {
                    LCD_Clear();
                    LCD_String_xy(1, 0, "Press Password");
                    LCD_Command(0xC0);
                    idx = -1;
                    memset(pass_user, 0, 5);
                } else break;
            } else pass_user[idx] = key;
            idx++;
        } while (1);
        LCD_Clear();
        LCD_String_xy(2, 2, "**Welcome Home**");
        delayms(100);
        LCD_Clear();
        showCustomCaracter(1, doorOpen);
        showCustomCaracter(3, doorClose);
        showCustomCaracter(5, windowsOpen);
        showCustomCaracter(7, windowsClose);
        LCD_Command(0xC0);
        timerInit();
        sensorMotion();
    }
}

void callRtc() {
    char secs[10], mins[10], hours[10];
    char date[10], month[10], year[10];
    char Clock_type = 0x06;
    char AM_PM = 0x05;
    char hora[21];
    char fecha[21];
    delayms(50);
    //OSCCON=0x72;                    /*Use internal oscillator and 
    // *set frequency to 8 MHz*/

    RTC_Read_Clock(0); /*gives second,minute and hour*/
    I2C_Stop();
    if (hour & (1 << Clock_type)) { /* check clock is 12hr or 24hr */

        if (hour & (1 << AM_PM)) { /* check AM or PM */
            LCD_String_xy(1, 14, "PM");
        } else {
            LCD_String_xy(1, 14, "AM");
        }

        hour = hour & (0x1f);
        sprintf(secs, "%x ", sec); /*%x for reading BCD format from RTC DS1307*/
        sprintf(mins, "%x:", min);
        sprintf(hours, "Tim:%x:", hour);
        LCD_String_xy(0, 0, hours);
        LCD_String(mins);
        LCD_String(secs);
    } else {

        hour = hour & (0x3f);
        sprintf(secs, "%x ", sec); /*%x for reading BCD format from RTC DS1307*/
        sprintf(mins, "%x:", min);
        sprintf(hours, "Tim:%x:", hour);
        LCD_String_xy(0, 0, hours);
        LCD_String(mins);
        LCD_String(secs);
    }

    RTC_Read_Calendar(3); /*gives day, date, month, year*/
    I2C_Stop();
    sprintf(date, "Cal %x-", Date);
    sprintf(month, "%x-", Month);
    sprintf(year, "%x ", Year);
    LCD_String_xy(2, 0, date);
    LCD_String(month);
    LCD_String(year);
    
}

void __interrupt() ISR_TIMER_0(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        TMR0H = 0xd9 >> 8; //Registro TMR1 =  55535 0xd8
        TMR0L = 0xab & 0xff; // 0xEF       
        INTCONbits.TMR0IF = 0;
        callRtc();
    }
}//*/

//void __interrupt() INT_EXT_0(void) {
//    if (INTCON2bits.INTEDG2) {
//        sensorMotion();
//        INTCON2bits.INTEDG2 = 0;
//    }
//}
 
void timerInit() {
    //Deshabilitar la Interrupción GLOBAL (para evitar Interrupciones falsas).
    INTCONbits.GIE = 0; //Deshabilita la interrupción global
    T0CONbits.T0CS = 0; //Timer1 en modo 8bits
    T0CONbits.PSA = 0; //Timer1 reloj interno = Fosc÷4
    T0CONbits.T08BIT = 0;
    T0CONbits.T0PS = 0b100; //Timer1 prescaler = 2       
    TMR0H = 0xd9 >> 8; //Registro TMR1 =  55535 0xd8
    TMR0L = 0xab & 0xff; // 0xEF
    T0CONbits.TMR0ON = 1; //Timer0 ON
    INTCONbits.TMR0IF = 0; //Borra flag de TIMER1
    INTCONbits.TMR0IE = 1; //Habilita interrupción TIMER1
    //INTCONbits.PEIE = 1; //Habilitara interrupción periféricas
    INTCONbits.GIE = 1; //Habilita interrupción global
}

void intInit() {
    INTCON3bits.INT2E = 1; //  Habilita interrupcion Externa INT0.
    INTCON2bits.INTEDG0 = 1; //  Interrupcion por flanco de bajada.
    INTCON3bits.INT2IF = 0; //  Borra el flag de INT0IF.
    RCONbits.IPEN = 0; //  Deshabilita las Interrupciones de Prioridad.
    INTCONbits.PEIE = 1; //  Habilita interrupciones PERIFERICAS.
    INTCONbits.GIE = 1; //  Habilita Interrupcion GLOBAL.
}

/**
 * init sensor motion
 */
void sensorMotion() {
    CNF_SENSOR = INPUT;
    CNF_LED_YELLOW = OUTPUT;
    LED_YELLOW = OFF;
    while (1) {
        while (MOTION_DETECTION) {
            LED_YELLOW = ON;
            BUZZER = ON;
        }
        LED_YELLOW = OFF;
        BUZZER = OFF;
    }
}

/**
 * show character custom to position (0-15) in row 1 and 2
 * @param pos
 * @param msg
 */
void showCustomCaracter(unsigned char pos, unsigned char *msg) {
    LCD_Custom_Char(pos, msg);
    LCD_Command(0x80 | (pos * 2 & 0x0f)); /*Display characters from c0(4nd row) location */
    LCD_Char(pos); /*To display custom character send address as data to point stored character */
}