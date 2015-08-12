/* 
 * File:   adc.h
 * Author: paolo
 *
 * Created on 23 marzo 2015, 9.31
 */

#ifndef ADC_H
#define	ADC_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    enum Thermocouple {
        THERM1,
        THERM2
    };

void initADC(void);
uint16_t readADC(int channel);
uint16_t getVolt(enum Thermocouple thermocouple);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

