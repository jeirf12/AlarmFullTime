/*
 * @File   Test.c
 * @Author jhonfer <jruizf@unicauca.edu.co>
 * @Author: Yaquelin Gomez
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

void startSystem();
void showInvalidSession();
void initComponentsMain();
void statusDoorWindows(unsigned char status);
unsigned char login();
void sensorMotion();
void showCustomCaracter(unsigned char pos, unsigned char *msg);
void callRtc();
void timerInit();
void intInit();
void __interrupt() ISR_TIMER_0(void);

/**
 * Start program chief
 * @return 
 */
int main() {
    unsigned char flag;
    initComponentsMain();
    while (1) {
        statusDoorWindows(0);
        flag = login();
        if (flag) {
            startSystem();
            break;
        } else {
            showInvalidSession();
        }
    }
}

/**
 * init all components system and desactive alarm
 */
void startSystem() {
    LCD_Clear();
    LCD_String_xy(2, 2, "**Welcome Home**");
    LCD_String_xy(3, 2, "Alarm Active");
    delayms(100);
    LCD_Clear();
    statusDoorWindows(1);
    intInit();
    timerInit();
    delayms(1000);
}

/**
 * show messages failed session
 */
void showInvalidSession() {
    LCD_Clear();
    LCD_String_xy(2, 0, "Exceeded the number");
    LCD_String_xy(3, 2, "of attempts");
    LCD_Clear();
    LCD_String_xy(2, 0, "wait 10 seconds");
    delayms(10000);
    LCD_Clear();
}

/**
 * init components chief
 */
void initComponentsMain() {
    ADCON1 = 0x0f;
    OSCCON = 0x72;
    CMCON = 0x07;
    initMemory();
    writeMemoryString(0, "2021");
    //chain = ReadMemoryString(0,3);
    I2C_Init();
    LCD_Init();
}

/**
 * show custom character by status
 * @param status
 */
void statusDoorWindows(unsigned char status) {
    if (status) {
        showCustomCaracter(3, doorClose);
        showCustomCaracter(7, windowsClose);
    } else {
        showCustomCaracter(1, doorOpen);
        showCustomCaracter(5, windowsOpen);
    }
}

/**
 * Login and verify user
 */
unsigned char login() {
    unsigned char key, status = 1, flag = 0;
    LCD_String_xy(2, 2, "Press Password");
    LCD_Command(0x94);
    do {
        if (flag < 3) {
            key = keyfind(); /* find a pressed key */
            LCD_Char('*'); /* display pressed key on LCD16x2 */
            if (key == 'o') {
                if (strcmp(&password, &pass_user) != 0) {
                    LCD_Clear();
                    statusDoorWindows(0);
                    LCD_String_xy(2, 2, "Press Password");
                    LCD_Command(0x94);
                    idx = -1;
                    flag += 1;
                    memset(pass_user, 0, 5);
                } else break;
            } else pass_user[idx] = key;
            idx++;
        } else {
            status = 0;
            break;
        }
    } while (1);
    return status;
}

/**
 * init sensor motion
 */
void sensorMotion() {
    CNF_SENSOR = INPUT;
    CNF_LED_YELLOW = OUTPUT;
    LED_YELLOW = OFF;
    if (MOTION_DETECTION) LED_YELLOW = ON;
    else LED_YELLOW = OFF;
}

/**
 * Init Real time clock
 */
void callRtc() {
    char secs[10], mins[10], hours[10];
    char date[10], month[10], year[10];
    char hora[21];
    char fecha[21];
    memset(hora, 0, 21);
    memset(fecha, 0, 21);

    RTC_Read_Clock(0); /*gives second,minute and hour*/
    I2C_Stop();
    hour = hour & (0x3f);
    sprintf(secs, "%x ", sec); /*%x for reading BCD format from RTC DS1307*/
    sprintf(mins, "%x:", min);
    sprintf(hours, "Tim:%x:", hour);
    strcat(hora, hours);
    strcat(hora, mins);
    strcat(hora, secs);
    LCD_String_xy(4, 0, hora);

    RTC_Read_Calendar(3); /*gives day, date, month, year*/
    I2C_Stop();
    sprintf(date, "Cal %x-", Date);
    sprintf(month, "%x-", Month);
    sprintf(year, "%x ", Year);
    strcat(fecha, date);
    strcat(fecha, month);
    strcat(fecha, year);
    LCD_String_xy(3, 0, fecha);
}

/**
 * Interrupt timer, sensor
 */
void __interrupt() ISR_TIMER_0(void) {
    if (INTCON2bits.INTEDG2) {
        sensorMotion();
        INTCON2bits.INTEDG2 = 0;
    }
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        TMR0H = 0xd9 >> 8; //Registro TMR1 =  55535 0xd8
        TMR0L = 0xab & 0xff; // 0xEF       
        INTCONbits.TMR0IF = 0;
        callRtc();
    }
}

/**
 * init interrupt timer real clock
 */
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

/**
 * init interrupt sensor motion
 */
void intInit() {
    INTCON3bits.INT2E = 1; //  Habilita interrupcion Externa INT0.
    INTCON2bits.INTEDG0 = 1; //  Interrupcion por flanco de bajada.
    INTCON3bits.INT2IF = 0; //  Borra el flag de INT0IF.
    RCONbits.IPEN = 0; //  Deshabilita las Interrupciones de Prioridad.
    INTCONbits.PEIE = 1; //  Habilita interrupciones PERIFERICAS.
    INTCONbits.GIE = 1; //  Habilita Interrupcion GLOBAL.
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