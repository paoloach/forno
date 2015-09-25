
#include <stdint.h>
#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include "RS232.h"



// Init at 38499 -->  SPBRG=77,  SPBRGH=0;

static volatile uint8_t outBuffer[256];
static volatile uint8_t * endOutBuffer = outBuffer + 256;
static volatile uint8_t * outWrite = outBuffer;
static volatile uint8_t * outRead = outBuffer;

static uint8_t inBuffer[512];
static uint8_t * endInBuffer = inBuffer + 512;
static uint8_t * inWrite = inBuffer;
static uint8_t * inRead = inBuffer;
static uint8_t * endSearch;

static uint8_t(* checkData)(void);

static uint8_t IPDdata;
static uint8_t * IPDIter;
static uint8_t * IPDdest;
static const char IPDstr[] = "+IPD,";
static char IPDexpected;
static uint8_t IPDIndex;
static uint8_t * endSearch;
static char bufferLen[10];
static char * bufferIter;
static uint16_t dataLen;
static int8_t result;

struct IPDStatusSearch {
    uint8_t IPDdataStartSearch : 1;
    uint8_t IPDdataFound : 1;
    uint8_t headerFound : 1;
    uint8_t channelFound : 1;
    uint8_t lenFound : 1;
    uint8_t waitForCR : 1;
    uint8_t waitForLF : 1;
};
static struct IPDStatusSearch IPDstatus;

uint8_t * rs232_getInBuffer(void) {
    return inBuffer;
}

void initRS232(void) {
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;

    TXSTAbits.BRGH = 1;
    BAUDCONbits.BRG16 = 1;

    SPBRG = 77; // 38400
    SPBRGH = 0;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;

    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;

    RCSTAbits.RC9 = 0;
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;

    PIR1bits.RCIF = 0;
    PIR1bits.TXIF = 0;
    PIE1bits.RC1IE = 1;
    PIE1bits.TXIE = 0;


    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

    IPDstatus.IPDdataStartSearch = 1;
}

void resetRS232(void) {
    inWrite = inBuffer;
    inRead = inBuffer;
    memset(inBuffer, 0, 512);
    IPDstatus.IPDdataStartSearch=1;
}

#ifndef TEST

void sendRS232(const uint8_t * data) {
    if (outWrite == outRead && *data != 0 && TXSTAbits.TRMT) {
        TXREG = *data;
        // outWrite++;
        data++;
        PIE1bits.TXIE = 1;
    }
    while (*data != 0) {
        while (outWrite != outRead && TXSTAbits.TRMT == 0);
        *outWrite = *data;
        outWrite++;
        data++;
        if (outWrite == endOutBuffer) {
            outWrite = outBuffer;
        }
    }
    PIE1bits.TXIE = 1;
}
#endif

void getRS232ReadData(unsigned char * dst, uint8_t size) {
    if (inRead < inWrite) {
        memcpy(dst, inRead, size);
        inRead += size;
    } else {
        uint8_t tmpSize = endInBuffer - inRead;
        if (size <= tmpSize) {
            memcpy(dst, inRead, size);
            inRead += size;
            if (inRead == endInBuffer) {
                inRead = inBuffer;
            }
            return;
        } else {
            memcpy(dst, inRead, tmpSize);
            dst += tmpSize;
            size -= tmpSize;
            memcpy(dst, inBuffer, size);
            inRead = inBuffer + size;
        }

    }
}

uint16_t getRS232ReadSize(void) {
    if (inWrite == inRead) {
        return 0;
    }

    if (inRead < inWrite) {
        return inWrite - inRead;
    } else {
        return (endInBuffer - inRead) + (inWrite - inBuffer);
    }
}

void RS232_ISR(void) {
    if (PIR1bits.TXIF) {
        if (outRead != outWrite) {
            TXREG = *outRead;
            outRead++;
            if (outRead == endOutBuffer) {
                outRead = outBuffer;
            }
        } else {
            PIE1bits.TXIE = 0;
        }
    }
    if (PIR1bits.RCIF) {
        PIR1bits.RCIF = 0;
        addRS232Char(RCREG);
    }
}

void addRS232Char(uint8_t data) {
    *inWrite = data;
    inWrite++;
    if (inWrite == endInBuffer) {
        inWrite = inBuffer;
    }
}

int8_t getLine(unsigned char * dst) {
    uint8_t * iter = inRead;
    uint8_t waitForLF = 0;
    uint8_t data;
    if (inRead == inWrite) {
        return 0;
    }
    if (inRead < inWrite) {
        while (iter != inWrite) {
            data = *iter;
            if (data < ' ') {
                if (data == '\r' && waitForLF == 0) {
                    waitForLF = 1;
                } else if (data == '\n' && waitForLF != 0) {
                    dst--;
                    *dst = 0;
                    inRead = iter + 1;
                    return 1;
                } else {
                    inRead = iter + 1;
                    return -1;
                }
            } else {
                *dst = data;
            }
            dst++;
            iter++;
        }
        return 0;
    } else {
        while (iter != endInBuffer) {
            data = *iter;
            if (data < ' ') {
                if (data == '\r' && waitForLF == 0) {
                    waitForLF = 1;
                } else if (data == '\n' && waitForLF != 0) {
                    dst--;
                    *dst = 0;
                    inRead = iter + 1;
                    return 1;
                } else {
                    inRead = iter + 1;
                    return -1;
                }
            } else {
                *dst = data;
            }
            dst++;
            iter++;
        }
        iter = inBuffer;
        while (iter != inWrite) {
            data = *iter;
            if (data < ' ') {
                if (data == '\r' && waitForLF == 0) {
                    waitForLF = 1;
                } else if (data == '\n' && waitForLF != 0) {
                    dst--;
                    *dst = 0;
                    inRead = iter + 1;
                    return 1;
                } else {
                    inRead = iter + 1;
                    return -1;
                }
            } else {
                *dst = data;
            }
            dst++;
            iter++;

        }
        return 0;
    }
}




static uint8_t checkIPDdata(void);
static void findIPDdata(void);
static uint8_t checkComma(void);
static uint8_t getLen(void);
static int8_t copyData(void);

int8_t getIPDLine(uint8_t * dst) {
    if (IPDstatus.IPDdataStartSearch) {
        IPDstatus.IPDdataFound = 0;
        IPDstatus.channelFound = 0;
        IPDstatus.headerFound = 0;
        IPDstatus.lenFound = 0;
        IPDIndex=0;
        IPDexpected = IPDstr[IPDIndex];
        IPDstatus.IPDdataStartSearch = 0;
        IPDstatus.waitForCR = 1;
        IPDstatus.waitForLF = 0;
    }
    if (IPDstatus.IPDdataFound == 0) {
        if (IPDstatus.headerFound == 0) {
            checkData = checkIPDdata;
            findIPDdata();
        }
        if (IPDstatus.headerFound && !IPDstatus.channelFound) {
            checkData = checkComma;
            findIPDdata();
        }
        if (IPDstatus.channelFound && !IPDstatus.lenFound) {
            checkData = getLen;
            findIPDdata();
        }
        if (IPDstatus.lenFound) {
            IPDstatus.IPDdataFound = 1;
        }
    }
    if (IPDstatus.IPDdataFound == 1) {

        if (inRead == inWrite) {
            return 0;
        }
        IPDdest = dst;
        IPDIter = inRead;
        if (IPDIter < inWrite) {
            endSearch = inWrite;
            result = copyData();
        } else {
            endSearch = endInBuffer;
            result = copyData();
            if (result == 0){
                IPDIter = inBuffer;
                endSearch = inWrite;
                result = copyData();
            }
        }
        if (dataLen == 0){
            IPDstatus.IPDdataStartSearch=1;
        }
        return result;
    }
    return 0;
}

static uint8_t checkIPDdata(void) {
    while (inRead != endSearch) {
        IPDdata = *inRead;
        if (IPDdata == IPDexpected) {
            IPDIndex++;
            IPDexpected = IPDstr[IPDIndex];
            if (IPDexpected == 0) {
                IPDstatus.headerFound = 1;
                inRead++;
                return 1;
            }
        }
        inRead++;
    }
    return 0;
}

static uint8_t checkComma() {
    while (inRead != endSearch) {
        IPDdata = *inRead;
        inRead++;
        if (IPDdata == ',') {
            IPDstatus.channelFound = 1;
            bufferIter = bufferLen;
            return 1;
        }

    }
    return 0;
}

static uint8_t getLen() {
    while (inRead != endSearch) {
        IPDdata = *inRead;
        *bufferIter = IPDdata;
        inRead++;
        if (IPDdata == ':') {
            *bufferIter = 0;
            IPDstatus.lenFound = 1;
            dataLen = atoi(bufferLen);
            return 1;
        }
        bufferIter++;

    }
    return 0;
}

static int8_t copyData() {
    while (IPDIter != endSearch && dataLen > 0) {
        IPDdata = *IPDIter;
        *IPDdest = IPDdata;
        IPDIter++;
        dataLen--;
        if (IPDdata == '\r')
            if (IPDstatus.waitForCR) {
                *IPDdest = 0;
                IPDstatus.waitForCR = 0;
                IPDstatus.waitForLF = 1;
            } else {
                inRead = IPDIter;
                return -1;
            }
        if (IPDdata == '\n') {
            if (IPDstatus.waitForLF) {
                *IPDdest = 0;
                IPDstatus.waitForCR = 1;
                IPDstatus.waitForLF = 0;
                inRead = IPDIter;
                return 1;
            } else {
                inRead = IPDIter;
                return -1;
            }
        }
        IPDdest++;
    }
    return 0;
}

static void findIPDdata(void) {
    if (inRead == inWrite) {
        return;
    }
    if (inRead < inWrite) {
        endSearch = inWrite;
        checkData();
    } else {
        endSearch = endInBuffer;
        if (checkData()) {
            return;
        }
        inRead = inBuffer;
        endSearch = inWrite;
        checkData();
    }
}

