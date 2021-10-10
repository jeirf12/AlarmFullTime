/* 
 * @File   MemoryEEPROM.h
 * @Author jhonfer <jruizf@unicauca.edu.co>
 * @Author: Yaquelin Gomez
 *
 * Created on September 22, 2021, 5:02 PM
 */
#include <pic18f4550.h>
#include <string.h>

#ifndef MEMORYEEPROM_H
#define	MEMORYEEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Start memory
 */
void initMemory();

/**
 * @brief write data in memory eeprom of pic
 * @param directionMemory
 * @param data
 */
void writeData(unsigned char directionMemory, unsigned char data);

/**
 * read data in memory eeprom of pic
 * @param directionMemory
 * @return data in memory
 */
unsigned char readData(unsigned char directionMemory);

/**
 * write string complete in memory of position initial
 * @param directionMemory
 * @param data
 */
void writeMemoryString(unsigned char directionMemory, const char *data);

/**
 * Read string complete with position initial and position end
 * @param directionMemoryInitial
 * @param directionMemoryEnd
 * @return chain complete
 */
unsigned char ReadMemoryString(unsigned char directionMemoryInitial,unsigned char directionMemoryEnd);

#ifdef	__cplusplus
}
#endif

#endif	/* MEMORYEEPROM_H */