
#include <xc.h>         /* XC8 General Include File */
#include "ADC.h"

void initADC(void){
    ADCON1bits.VCFG1=1;
    ADCON1bits.VCFG0=1;
    ADCON1bits.PCFG = 0xB;

    ADCON0bits.CHS = 0;

    ADCON2bits.ACQT = 0;
    ADCON2bits.ADCS = 0x7;
    ADCON2bits.ADFM=1;

    ADCON0bits.ADON=1;
}

uint16_t readADC(int channel){
    ADCON0bits.CHS = channel;
    Delay10TCYx(30);
    PIR1bits.ADIF=0;
    ADCON0bits.GO=1;
//    SLEEP();
    while(ADCON0bits.GO == 1);
    return ADRES;
}
#define VREF_M 2.5
#define VREF_P VREF_M*(1+3.3/4.7)
uint16_t getVolt(enum Thermocouple thermocouple){
    int channel = 0;
    switch(thermocouple){
        case THERM1:
            channel = 0;
            break;
        case THERM2:
            channel = 1;
            break;
    }
    
    uint16_t adc = readADC(channel);
    return (uint16_t)( 1000.0*((adc*(VREF_P-VREF_M))/1024.0+VREF_M));
}