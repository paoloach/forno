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
#include <pic18f4620.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "LCD.h"
#include "ADC.h"
#include "TempConverter.h"
#include "DS18B20.h"
#include "RS232.h"
#include "PWM.h"
#include "webServer.h"



/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
typedef unsigned char bool;
char  buffer[16];
int status=0;
uint16_t localTemp;
uint16_t thereshold=110;;
uint16_t tempReal=0;
uint16_t temp1;
uint16_t temp2;
uint16_t temp;
uint8_t  enable=1;
struct ButtonStatus {
    unsigned char plus  :1;
    unsigned char minus  :1;
};

struct ButtonStatus buttonStatus;

void printLocalTemp(unsigned char line);
void printInternalTemp(unsigned char line);
void printThereshold(unsigned char line);
bool isBtPlus();

void main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();
    

    
    /* Initialize I/O and Peripherals for application */
    InitApp();
   
#ifdef TEST
    RS232_TEST();
    while(1);
#endif

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    localTemp=0;
    tempReal=0;
    startDS18B20();
    while(1) {
        localTemp = getDS18B20();
        uint16_t mv1 = getVolt(THERM1);
        uint16_t mv2 = getVolt(THERM2);
        temp = tempConvert(mv1);
        temp2 = tempConvert(mv2);
        temp2 = (temp1 + temp2)/2;

        if (localTemp != 0xFF){
            startDS18B20();
            tempReal = localTemp + temp;
        }
        itoa(buffer,temp,10);
     
        if (tempReal > thereshold || enable!=1 ){
            disableOut();
        } else {
            enableOut();
        }
        if (isBtPlus()){
            thereshold++;
        }
    }

}


void printLocalTemp(unsigned char line) {
    memset(buffer,' ',16);
    itoa(buffer,localTemp,10);
    if (line==1){
        line1();
    } else {
        line2();
    }
    writeLCDC(buffer,16);
}

void printThereshold(unsigned char line) {
    memset(buffer,' ',16);
    itoa(buffer,thereshold,10);
    if (line==1){
        line1();
    } else {
        line2();
    }
    writeLCDC(buffer,16);
}
 
void printInternalTemp(unsigned char line){
    memset(buffer,' ',16);
    itoa(buffer,tempReal,10);
    if (line==1){
        line1();
    } else {
        line2();
    }

    writeLCDC(buffer,16);
}

bool isBtPlus() {
    bool result=false;
    if (PORTBbits.RB1 == 0){
        _delay(1);
        if (PORTBbits.RB1 == 0){
            _delay(1);
            if (PORTBbits.RB1 == 0){
                buttonStatus.plus = 0;
            }
        }
    } else {
        if (PORTBbits.RB1 == 1){
            _delay(1);
            if (PORTBbits.RB1 == 1){
                _delay(1);
                if (PORTBbits.RB1 == 1){
                    if (buttonStatus.plus == 0){
                        result = true;
                    }
                    buttonStatus.plus = 1;
                }
            }
        }
    }
    
    return result;
}