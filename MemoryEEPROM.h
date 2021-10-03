/* 
 * @File   MemoryEEPROM.h
 * @Author jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on September 22, 2021, 5:02 PM
 */
#include <pic18f4550.h>

#ifndef MEMORYEEPROM_H
#define	MEMORYEEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

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


#ifdef	__cplusplus
}
#endif

#endif	/* MEMORYEEPROM_H */

