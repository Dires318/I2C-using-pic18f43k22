/* 
 * File:   newfile.h
 * Author: Dires
 *
 * Created on January 1, 2020, 10:51 AM
 */

#pragma config MCLRE = EXTMCLR, WDTEN = OFF
//FOSC = INTIO7
#define _XTAL_FREQ 8000000

#include <xc.h>
void config();
void Send_I2C_StartBit(void);
void Send_I2C_StopBit( void);
void Send_I2C_Repeated_Start ( void);
void Send( unsigned char x);
unsigned int Read_I2C_Data( void);
void wait();
void configure();
void interapt();
void address();
unsigned char receive();
void release();
void wait_clearInterapt();
#ifndef NEWFILE_H
#define	NEWFILE_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* NEWFILE_H */

