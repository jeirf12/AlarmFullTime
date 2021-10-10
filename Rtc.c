/* 
 * @File: Rtc.c
 * @Author: jhonfer <jruizf@unicauca.edu.co>
 * @Author: Yaquelin Gomez
 * @brief Libreria para control del RTC
 * Created on 27 April 2021, 15:44
 */

#include "Rtc.h"

/**
 * Rtc Read clock 
 * @param read_clock_address
 */
void RTC_Read_Clock(char read_clock_address){
    I2C_Start(device_id_write);
    I2C_Write(read_clock_address);     /* address from where time needs to be read*/
    I2C_Repeated_Start(device_id_read);
    sec = I2C_Read(0);                 /*read data and send ack for continuous reading*/
    min = I2C_Read(0);                 /*read data and send ack for continuous reading*/
    hour = I2C_Read(1);                 /*read data and send nack for indicating stop reading*/
}

/**
 * Read calendar of rtc
 * @param read_calendar_address
 */
void RTC_Read_Calendar(char read_calendar_address){   
    I2C_Start(device_id_write);
    I2C_Write(read_calendar_address); /* address from where time needs to be read*/
    I2C_Repeated_Start(device_id_read);
    Day = I2C_Read(0);                /*read data and send ack for continuous reading*/
    Date = I2C_Read(0);               /*read data and send ack for continuous reading*/
    Month = I2C_Read(0);              /*read data and send ack for continuous reading*/
    Year = I2C_Read(1);               /*read data and send nack for indicating stop reading*/
    I2C_Stop();
}