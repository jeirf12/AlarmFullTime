/*
 * @File: Rtc.h
 * @Author: jhonfer <jruizf@unicauca.edu.co>
 * @Author: Yaquelin Gomez
 * @brief Libreria para control del RTC
 * Created on 27 April 2021, 15:44
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include "I2C.h"

#define device_id_write 0xD0
#define device_id_read 0xD1
int sec, min, hour;
int Day, Date, Month, Year;

/**
 * Rtc Read clock 
 * @param read_clock_address
 */
void RTC_Read_Clock(char read_clock_address);

/**
 * Read calendar of rtc
 * @param read_calendar_address
 */
void RTC_Read_Calendar(char read_calendar_address);

#endif /*XC_HEADER_TEMPLATE_H */