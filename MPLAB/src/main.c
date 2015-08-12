/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include <stdlib.h>
#include <string.h>
#include <delays.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "LCD.h"
#include "ADC.h"
#include "TempConverter.h"
#include "DS18B20.h"
#include "RS232.h"


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
char  buffer[16];
int status;
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    uint16_t localTemp=0;
    uint16_t dataCount=0;
    startDS18B20();
    while(1) {
        localTemp = getDS18B20();
        uint16_t mv1 = getVolt(THERM1);
        uint16_t mv2 = getVolt(THERM2);
        uint16_t mean = (mv1 + mv2)/2;
        uint16_t temp = tempConvert(mv1);
        if (localTemp != 0xFF){
            itoa(buffer,localTemp,10);
            line2();
            writeLCD(buffer);
            writeLCD("    ");
       
            itoa(buffer,temp+localTemp,10);
            line1();
            writeLCD(buffer);
            writeLCD("    ");
            startDS18B20();
        }
        itoa(buffer,temp,10);
        for(uint8_t i=0; buffer[i] != 0; i++){
            sendRS232(buffer[i]);
            dataCount++;
        }
        if (localTemp != 0xFF){
            sendRS232('\n');
            sendRS232('\r');
            itoa(buffer,dataCount,10);
            for(uint8_t i=0; buffer[i] != 0; i++){
                sendRS232(buffer[i]);
            }
            sendRS232(',');
            sendRS232(' ');
            dataCount=0;
        } else {
            sendRS232(',');
            sendRS232(' ');
        }
        
    }

}

