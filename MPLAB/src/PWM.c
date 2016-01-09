
#include <xc.h>
#include "PWM.h"

void initPWM(void) {
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;
    
    PORTCbits.RC1 = 1;
    PORTCbits.RC2 = 1;
}

void enableOut(void) {
    unsigned char latc = LATC;
    latc |= 0x06;
    LATC = latc;
}
void disableOut(void) {
    unsigned char latc = LATC;
    latc &= 0xF9;
    LATC = latc;
}

