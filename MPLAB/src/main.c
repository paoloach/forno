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
#include <pic18f4620.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "LCD.h"
#include "ADC.h"
#include "TempConverter.h"
#include "DS18B20.h"
#include "RS232.h"
#include "PWM.h"



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

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    localTemp=0;
    uint16_t dataCount=0;
    tempReal=0;
    startDS18B20();
    while(1) {
        localTemp = getDS18B20();
        uint16_t mv1 = getVolt(THERM1);
        uint16_t mv2 = getVolt(THERM2);
        uint16_t mean = (mv1 + mv2)/2;
        uint16_t temp = tempConvert(mv1);

        if (localTemp != 0xFF){
            printInternalTemp(1);
            //printLocalTemp(2);
            printThereshold(2);
            
            startDS18B20();
            tempReal = localTemp + temp;
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
        
        if (tempReal > thereshold ){
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
        Delay1TCYx(1);
        if (PORTBbits.RB1 == 0){
            Delay1TCYx(1);
            if (PORTBbits.RB1 == 0){
                buttonStatus.plus = 0;
            }
        }
    } else {
        if (PORTBbits.RB1 == 1){
            Delay1TCYx(1);
            if (PORTBbits.RB1 == 1){
                Delay1TCYx(1);
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