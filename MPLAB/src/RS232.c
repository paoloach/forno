
#include <stdint.h>
#include <xc.h>
#include "RS232.h"

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

}

void sendRS232(uint8_t data){
    while(PIR1bits.TXIF==0);
    PIR1bits.TXIF=0;
    TXREG=data;
}
