/* 
 * @File   MemoryEEPROM.c
 * @Author jhonfer <jruizf@unicauca.edu.co>
 * @Author: Yaquelin Gomez
 * Created on 27 April 2021, 15:44
 */

#include <xc.h>
#include "MemoryEEPROM.h"

/**
 * Start memory
 */
void initMemory(){
    TRISD = 0;
    LATD = 0;
}

/**
 * @brief write data in memory eeprom of pic
 * @param directionMemory
 * @param data
 */
void writeData(unsigned char directionMemory, unsigned char data){
    EEADR = directionMemory;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0x0AA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;
    while(!PIR2bits.EEIF);
    PIR2bits.EEIF = 0;
    EECON1bits.WREN = 0;
}

/**
 * read data in memory eeprom of pic
 * @param directionMemory
 * @return data in memory
 */
unsigned char readData(unsigned char directionMemory){
    EEADR = directionMemory;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;  /* start read */
    return EEDATA;
}

/**
 * write string complete in memory of position initial
 * @param directionMemory
 * @param data
 */
void writeMemoryString(unsigned char directionMemory, const char *data){
    unsigned char counter = directionMemory;
    while(*data != 0){
        writeData(counter, *data);
        counter++;
        data++;
    }  
}

/**
 * Read string complete with position initial and position end
 * @param directionMemoryInitial
 * @param directionMemoryEnd
 * @return chain complete
 */
unsigned char ReadMemoryString(unsigned char directionMemoryInitial,unsigned char directionMemoryEnd){
    unsigned char counter = directionMemoryInitial, chain[5];
    while(counter <= directionMemoryEnd){
        strcat(chain, readData(counter));
        counter++;
    }
    return chain;
}