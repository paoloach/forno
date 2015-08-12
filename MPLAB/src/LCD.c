#include <stdint.h>
#include <delays.h>
#include "LCD.h"

#include <xc.h>         /* XC8 General Include File */

#define CLOCK 12000000
#define TICK_FOR_MICROSEC CLOCK/(4*1000000)

static void waitForLCDStart(void);
static void waitFor30ms(void);
static void waitFor39us(void);
static void waitFor2ms(void);
static void writeCmdLCD(uint8_t data);
static void waitNotBusy(void);

#define RS LATEbits.LE0
#define RW LATEbits.LE1
#define E  LATEbits.LE2

void initLCD(void){
        /* Enable interrupts */
    TRISD=0;
    TRISE0 = 0;
    TRISE1 = 0;
    TRISE2 = 0;
    RS=0;
    RW=0;
    E=0;
    waitForLCDStart();
    line1();
    writeLCD("line1");
    line2();
    writeLCD("line2");
}

void line1(void) {
    writeCmdLCD(0x80);
}

void line2(void) {
    writeCmdLCD(0xC0);
}

void writeLCD(const char * str){
    while(*str != 0){
        writeDataLCD(*str);
        str++;
    }
}



static void waitForLCDStart(void){
    waitFor30ms();
    writeCmdLCD(0x38);
    waitFor39us();
    writeCmdLCD(0x0F);
    waitFor39us();
    writeCmdLCD(0x01);
    waitFor2ms();
    writeCmdLCD(0x06);
}

static void waitFor30ms(void) {
     for(uint8_t i=0; i< 30;i++ ){
        Delay100TCYx(TICK_FOR_MICROSEC*10);
    }
}

static void waitFor2ms(void){
    Delay100TCYx(TICK_FOR_MICROSEC*10);
    Delay100TCYx(TICK_FOR_MICROSEC*10);
}

static void waitFor39us(void) {
    Delay1TCYx(TICK_FOR_MICROSEC*39);
}

void writeDataLCD(char data){
    waitNotBusy();
    RS=1;
    RW=0;
    E=1;
    PORTD=data;
    E=0;
}


static void writeCmdLCD(uint8_t data){
    waitNotBusy();
    RS=0;
    RW=0;
    E=1;
    PORTD=data;
    E=0;
}

static void waitNotBusy(void){
    TRISD=0xFF;
    uint8_t res=0;
    RS=0;
    RW=1;
    do {
        E=1;
        Delay1TCY();
        Delay1TCY();
        if (PORTDbits.RD7 == 0){
            res=1;
        }
        E=0;
    } while (res == 0);
    TRISD=0;
    return;
}