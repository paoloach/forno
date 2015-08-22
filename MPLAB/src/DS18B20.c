
#include <xc.h>
#include <stdint.h>

#include "DS18B20.h"

#define CLOCK 12000000
#define TICK_FOR_MICROSEC CLOCK/(4*1000000

static void writeDS(unsigned char data);
static unsigned char reset();
static uint8_t readDS(void);
static void waitEndConvert(void);

void startDS18B20(void){
    LATCbits.LATC0=0;
    T0CON = 0x88;
    if (reset() == 0){
        return;
    }
    writeDS(0xCC);
    writeDS(0x44);
}

unsigned char getDS18B20(void) {
    uint8_t tempLow;
    uint8_t tempHeight;
    uint16_t temp;
    TRISCbits.RC0 = 0;
    _delay(4);
    TRISCbits.RC0 = 1;
    _delay(4);
    if (PORTCbits.RC0 == 0){
        return 0xFF;
    }
    _delay(250);
    reset();
    writeDS(0xCC);
    writeDS(0xBE);
    tempLow =  readDS();
    tempHeight = readDS();

    temp = tempLow + (tempHeight << 8);
    return temp >> 4;
}

static void waitEndConvert(void){
    while(1){
        TRISCbits.RC0 = 0;
        _delay(4);
        TRISCbits.RC0 = 1;
        _delay(4);
        if (PORTCbits.RC0 == 1){
            _delay(250);
            return;
        }
        _delay(250);
    };
}

static unsigned char reset(){

    TRISCbits.RC0 = 0;
    _delay(1920);
    TRISCbits.RC0 = 1;
    _delay(250);
    if (PORTCbits.RC0){
        return 0;
    }
    _delay(1920-250);
    return 1;
}

static uint8_t readDS(){
    uint8_t data=0;
    for(uint8_t i=0; i < 8; i++){
        TRISCbits.RC0 = 0;
        _delay(4);
        TRISCbits.RC0 = 1;
        _delay(4);
        data = data >> 1;
        if (PORTCbits.RC0==1){
            data |= 0x80;
        }
        _delay(120);
    }
    return data;
}

static void writeDS(unsigned char data){
    for(uint8_t i=0; i < 8; i++){
        TRISCbits.RC0 = 0;
        if (data & 0x1){
            NOP();
            NOP();
            NOP();
            TRISCbits.RC0=1;
            NOP();
            _delay(150);
        } else {
            _delay(150);
            TRISCbits.RC0=1;
        }
        data = data >> 1;
    }
}