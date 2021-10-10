/* 
 * @File   I2C.h
 * @Author jhonfer <jruizf@unicauca.edu.co>
 * @Author: Yaquelin Gomez
 *
 * Created on 14 September 2021, 16:37
 */
 
#ifndef I2C_H
#define	I2C_H

#ifdef __cplusplus
extern "C" {
#endif /* end macro __cplusplus */

#include <xc.h> // include processor files - each processor file is guarded.  

#define F_OSC 8000000                       /* define F_OSC for finding bit rate here oscillator frequency is 8 MHz so define as 800000 */
#define I2C_CLOCK 100000                    /* I2C clock frequency is 100 kHz*/
#define BITRATE ((F_OSC/(4*I2C_CLOCK))-1)  /* find bit rate to assign this value to SSPADD register*/

/**
 * check and wait weather I2C is ready or not
 */
void I2C_Ready();                           

/**
 * @brief initialize I2C register configuration
 */
void I2C_Init();                            

/**
 * send start pulse along with slave device address
 * @param slave_write_address
 * @return 
 */
char I2C_Start(char);                       

/**
 * send start pulse along with slave device address and wait if not work
 * @param slave_write_address
 */
void I2C_Start_Wait(char);                  

/**
 * send repeated start pulse along with device write address
 * @param slave_read_address
 * @return 
 */
char I2C_Repeated_Start(char);              

/**
 * send stop pulse
 * @return operation stop
 */
char I2C_Stop();                            

/**
 * transmit/write data/address to slave device
 * @param data
 * @return 
 */
char I2C_Write(unsigned char);              

/**
 * send acknowledge from master for another read
 */
void I2C_Ack();

/**
 * send negative acknowledge from master for stop reading
 */
void I2C_Nack();

/**
 * read data from slave devices
 * @param flag
 * @return buffer
 */
char I2C_Read(char flag);

#ifdef __cplusplus
}
#endif /* end macro __cplusplus */
#endif	/* I2C_H */