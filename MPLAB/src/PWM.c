
#include <xc.h>
#include "PWM.h"

void initPWM(void) {
    TRISCbits.RC1=0;
    
    PORTCbits.RC1 = 1;
}

void enableOut(void) {
    unsigned char latc = LATC;
    latc |= 0x02;
    LATC = latc;
}
void disableOut(void) {
    unsigned char latc = LATC;
    latc &= 0xFD;
    LATC = latc;
}

