/* 
 * File:   RS232.h
 * Author: paolo
 *
 * Created on 25 marzo 2015, 12.54
 */

#ifndef RS232_H
#define	RS232_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif



void initRS232(void);
void sendRS232(const uint8_t * data);
void RS232_ISR(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RS232_H */

