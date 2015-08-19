
#include <stdint.h>
#include <xc.h>
#include "RS232.h"


// Init at 38499 -->  SPBRG=77,  SPBRGH=0;

static volatile uint8_t outBuffer[256];
static volatile uint8_t * endOutBuffer = outBuffer + 256;
static volatile uint8_t * outWrite = outBuffer;
static volatile uint8_t * outRead = outBuffer;


void initRS232(void) {
    TRISCbits.RC6=1;
    TRISCbits.RC7=1;
    
    TXSTAbits.BRGH=1;
    BAUDCONbits.BRG16=1;

    SPBRG=77;  // 38400
    SPBRGH=0;
    TXSTAbits.SYNC=0;
    RCSTAbits.SPEN=1;

    TXSTAbits.TX9=0;
    TXSTAbits.TXEN=1;
    
    RCSTAbits.RC9=0;
    RCSTAbits.CREN=0;

    PIR1bits.TXIF=0;
    PIE1bits.TXIE=0;
    
    RCONbits.IPEN = 1;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    
}

void sendRS232(const uint8_t * data){
    if (outWrite == outRead && *data != 0 && TXSTAbits.TRMT){
        TXREG = *data;
       // outWrite++;
        data++;
        PIE1bits.TXIE=1;
    }
    while (*data != 0){
        while (outWrite != outRead && TXSTAbits.TRMT == 0);
        *outWrite = *data;
        outWrite++ ;
        data++;
        if (outWrite == endOutBuffer){
            outWrite = outBuffer;
        }
    }
    PIE1bits.TXIE=1;
}


void RS232_ISR(void) {
    if (PIR1bits.TXIF){
        if (outRead != outWrite){
            TXREG = *outRead;
            outRead ++;
            if (outRead == endOutBuffer){
                outRead = outBuffer;
            } 
        } else {
            PIE1bits.TXIE=0;
        }
    }
}
