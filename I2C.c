/* 
 * @File   I2C.c
 * @Author jhonfer <jruizf@unicauca.edu.co>
 * @Author: Yaquelin Gomez
 *
 * Created on 14 September 2021, 16:37
 */

#include "I2C.h"

/**
 * read data from slave devices
 * @param flag
 * @return buffer
 */
char I2C_Read(char flag) { /*read data from location and send ack or nack depending upon parameter*/
    char buffer;
    RCEN = 1; /*enable receive*/
    while (!SSPSTATbits.BF); /*wait for buffer full flag which is set when complete byte received*/
    buffer = SSPBUF; /*copy SSPBUF to buffer*/
    /*send acknowledgment or negative acknowledgment */
    if (flag == 0)
        I2C_Ack();
    else
        I2C_Nack();
    I2C_Ready();
    return (buffer);
}

/**
 * @brief initialize I2C register configuration
 */
void I2C_Init() {
    TRISB0 = 1; /*set up I2C lines by setting as input*/
    TRISB1 = 1;
    SSPSTAT = 80; /*slew rate disabled, other bits are cleared*/
    SSPCON1 = 0x28; /*enable SSP port for I2C Master mode,clock = FOSC / (4 * (SSPADD+1))*/
    SSPCON2 = 0;
    SSPADD = BITRATE; /*clock 100 kHz*/
    SSPIE = 1; /*enable SSPIF interrupt*/
    SSPIF = 0;
}

/**
 * check and wait weather I2C is ready or not
 */
void I2C_Ready() {
    while (!SSPIF); /* Wait for operation complete */
    SSPIF = 0; /*clear SSPIF interrupt flag*/
}

/**
 * send start pulse along with slave device address and wait if not work
 * @param slave_write_address
 */
void I2C_Start_Wait(char slave_write_address) {
    while (1) {
        SSPCON2bits.SEN = 1; /*send start pulse*/
        while (SSPCON2bits.SEN); /*wait for completion of start pulse*/
        SSPIF = 0;
        if (!SSPSTATbits.S) /*wait till start bit is detected*/
            continue;
        I2C_Write(slave_write_address); /*write slave device address with write to communicate*/
        if (ACKSTAT) {
            I2C_Stop();
            continue;
        }
        break;
    }
}

/**
 * send start pulse along with slave device address
 * @param slave_write_address
 * @return 
 */
char I2C_Start(char slave_write_address) {
    SSPCON2bits.SEN = 1; /*send start pulse*/
    while (SSPCON2bits.SEN); /*wait for completion of start */
    SSPIF = 0;
    if (!SSPSTATbits.S) /*wait till start bit is detected*/
        return 0; /*start failed*/
    return (I2C_Write(slave_write_address)); /*write slave device address with write to communicate*/
}

/**
 * send repeated start pulse along with device write address
 * @param slave_read_address
 * @return 
 */
char I2C_Repeated_Start(char slave_read_address) {
    RSEN = 1; /*send repeated start pulse*/
    while (RSEN); /*wait for completion of repeated start pulse*/
    SSPIF = 0;
    if (!SSPSTATbits.S) /*wait till start bit is detected*/
        return 0; /*start failed*/
    I2C_Write(slave_read_address); /*write slave device address with read to communicate*/
    if (ACKSTAT)
        return 1;
    else
        return 2;
}

/**
 * send stop pulse
 * @return operation stop
 */
char I2C_Stop() {
    PEN = 1; /*stop communication*/
    while (PEN); /*wait for end of stop pulse*/
    if (!SSPSTATbits.P); /*wait till stop bit is detected*/
    return 0; /*stop failed*/
}

/**
 * transmit/write data/address to slave device
 * @param data
 * @return 
 */
char I2C_Write(unsigned char data) {
    SSPBUF = data; /*write data to SSPBUF*/
    I2C_Ready();
    if (ACKSTAT) /*check for acknowledge bit*/
        return 1;
    else
        return 2;
}

/**
 * send acknowledge from master for another read
 */
void I2C_Ack() {
    ACKDT = 0; /*acknowledge data 1:NACK,0:ACK */
    ACKEN = 1; /*enable ACK to send*/
    while (ACKEN);
}

/**
 * send negative acknowledge from master for stop reading
 */
void I2C_Nack() {
    ACKDT = 1; /*acknowledge data 1:NACK,0:ACK*/
    ACKEN = 1; /*enable ACK to send*/
    while (ACKEN);
}