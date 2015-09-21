/* 
 * File:   RS232.h
 * Author: paolo
 *
 * Created on 25 marzo 2015, 12.54
 */

#ifndef RS232_H
#define	RS232_H

#include <stdint.h>
#include <xc.h>
#include <stdlib.h>
#include <string.h>


#ifdef	__cplusplus
extern "C" {
#endif



void initRS232(void);
void sendRS232(const uint8_t * data);
void RS232_ISR(void);
uint16_t getRS232ReadSize(void);
void getRS232ReadData(unsigned char * dst, uint8_t size);
int8_t getLine(unsigned char * dst);

void resetRS232(void);
void addRS232Char(uint8_t data);
uint8_t * rs232_getInBuffer(void);

#ifdef TEST
void RS232_TEST(void);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* RS232_H */

