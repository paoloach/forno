#include <stdint.h>
#include <xc.h>
#include <stdlib.h>
#include <string.h>

#include "RS232.h"
#include "webServer.h"
#include "unity.h"

uint16_t localTemp;
uint16_t threshold;
uint16_t tempReal;
uint16_t temp1;
uint16_t temp2;
uint16_t temp;
uint8_t enable;

struct RS232Action {
    const char * string;
    void (* action)(void);
    uint8_t callCount;
};

static const char str1[] = "first data ";
static const char str2[] = "second data ";
static const char str_20bytes[] = "01234567890123456789";
static char buffer[100];
static char txBuffer[100];
static char * txBufferIn;
static char * txBufferOut;
static struct RS232Action rs232Actions[10];
static uint8_t actionsCount = 0;

void sendRS232(const uint8_t * data) {
    while (*data != 0) {
        *txBufferIn = *data;
        txBufferIn++;
        data++;
    }
    for (uint8_t i = 0; i < actionsCount; i++) {
        uint8_t len = strlen(rs232Actions[i].string);
        if (memcmp(rs232Actions[i].string, txBufferOut, len) == 0) {
            rs232Actions[i].callCount = 1;
            rs232Actions[i].action();
            txBufferOut += len;
            break;
        }
    }
}

void setUp() {
    txBufferIn = txBuffer;
    txBufferOut = txBuffer;
    actionsCount = 0;
    resetRS232();
}

void verifyActions() {
    for (uint8_t i = 0; i < actionsCount; i++) {
        if (rs232Actions[i].callCount == 0) {
            UnityPrint("Action for ");
            UnityPrint(rs232Actions[i].string);
            UnityPrint(" never called - ");
        }
    }
}

void tearDown() {
    verifyActions();
}

void addAction(const char * string, void (* action)(void)) {
    rs232Actions[actionsCount].string = string;
    rs232Actions[actionsCount].action = action;
    rs232Actions[actionsCount].callCount = 0;
    actionsCount++;
}

void addString(const char * str) {
    while (*str != 0) {
        addRS232Char(*str);
        str++;
    }
}

void addLine(const char * str) {
    while (*str != 0) {
        addRS232Char(*str);
        str++;
    }
    addRS232Char('\r');
    addRS232Char('\n');
}

void moveReadPointerToEndMinus(uint8_t minus) {
    for (uint16_t i = 0; i < 512 - minus; i++) {
        addRS232Char('a');
    }
    for (uint16_t i = 0; i < 512 - minus; i++) {
        getRS232ReadData(buffer, 1);
    }
}

void test_firstData(void) {
    addString(str1);
    int len = sizeof (str1) - 1;
    TEST_ASSERT_EQUAL(len, getRS232ReadSize());
    getRS232ReadData(buffer, len);
    TEST_ASSERT_EQUAL_STRING(str1, buffer);
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_readDataAfterData(void) {
    addString(str1);
    getRS232ReadData(buffer, 5);
    buffer[5] = 0;
    TEST_ASSERT_EQUAL_STRING("first", buffer);
    TEST_ASSERT_EQUAL(6, getRS232ReadSize());
    getRS232ReadData(buffer, 6);
    buffer[6] = 0;
    TEST_ASSERT_EQUAL_STRING(" data ", buffer);
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_roundInsert(void) {
    for (uint16_t i = 0; i < 500; i++) {
        addRS232Char('a');
    }
    for (uint16_t i = 0; i < 5; i++) {
        getRS232ReadData(buffer, 100);
    }
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
    addString(str_20bytes);
    TEST_ASSERT_EQUAL(20, getRS232ReadSize());
    getRS232ReadData(buffer, 20);
    buffer[20] = 0;
    TEST_ASSERT_EQUAL_STRING(str_20bytes, buffer);
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_get1Line(void) {
    addLine(str1);
    int len = sizeof (str1) - 1;
    TEST_ASSERT_EQUAL(len + 2, getRS232ReadSize());
    TEST_ASSERT_EQUAL(1, getLine(buffer));
    TEST_ASSERT_EQUAL_STRING(str1, buffer);
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_get2Lines(void) {
    addLine(str1);
    addLine(str2);
    int len = sizeof (str1) + sizeof (str2) - 1 - 1;
    TEST_ASSERT_EQUAL(len + 4, getRS232ReadSize());
    TEST_ASSERT_EQUAL(1, getLine(buffer));
    TEST_ASSERT_EQUAL_STRING(str1, buffer);
    TEST_ASSERT_EQUAL(1, getLine(buffer));
    TEST_ASSERT_EQUAL_STRING(str2, buffer);
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_foundLineRound(void) {
    for (uint16_t i = 0; i < 500; i++) {
        addRS232Char('a');
    }
    for (uint16_t i = 0; i < 5; i++) {
        getRS232ReadData(buffer, 100);
    }
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
    addLine(str_20bytes);
    TEST_ASSERT_EQUAL(22, getRS232ReadSize());
    TEST_ASSERT_EQUAL(1, getLine(buffer));
    TEST_ASSERT_EQUAL_STRING(str_20bytes, buffer);
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_lineNotFound(void) {
    addString(str1);
    TEST_ASSERT_EQUAL(0, getLine(buffer));
}

void test_simpleIPDData() {
    addString("+IPD,0,14:line1\r\nline2\r\n");
    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 0);
}

void test_IPDDataWithPreviousResponse() {
    addString("LINK OK\r\n+IPD,0,14:line1\r\nline2\r\n");
    TEST_ASSERT_EQUAL(1,getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 0);
}

void test_twoIPData() {
    addString("+IPD,0,14:line1\r\nline2\r\n");
    addString("+IPD,0,14:line3\r\nline4\r\n");
    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line3", buffer);
    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line4", buffer);
    TEST_ASSERT_EQUAL(0, getIPDLine(buffer));
}

void test_IPDroundPayload(void) {
    moveReadPointerToEndMinus(12);
    addString("+IPD,0,14:line1\r\nline2\r\n");

    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(0, getIPDLine(buffer));
}

void test_IPDroundLenPayload(void) {
    moveReadPointerToEndMinus(8);
    addString("+IPD,0,14:line1\r\nline2\r\n");

    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(0, getIPDLine(buffer));
}

void test_IPDroundChannel(void) {
    moveReadPointerToEndMinus(6);
    addString("+IPD,000,14:line1\r\nline2\r\n");

    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(0, getIPDLine(buffer));
}

void test_IPDroundHeader(void) {
    moveReadPointerToEndMinus(2);
    addString("+IPD,0,14:line1\r\nline2\r\n");

    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(1, getIPDLine(buffer));
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(0, getIPDLine(buffer));
}

void respondOK() {
    addLine("OK");
}

void test_InitWebServer() {
    addAction("AT+CWMODE=3\r\n", respondOK);
    addAction("AT+CIPMUX=1\r\n", respondOK);
    addAction("AT+CIPSERVER=1,8080\r\n", respondOK);
    initWebServer();
    TEST_ASSERT_TRUE(isWebServerOn());
}


void nullAction() {
}

void putSendChar() {
    addString(">");
}

void putSendOK() {
    addLine("SEND OK");
}


const char  GET_temp[] = "+IPD,0,425:"\
"GET /temp HTTP/1.1\r\n"\
"Host: 127.0.0.1\r\n" \
"Connection: keep-alive\r\n" \
"Cache-Control: max-age=0\r\n"  \
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n" \
"Upgrade-Insecure-Requests: 1\r\n" \
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36\r\n" \
"Accept-Encoding: gzip, deflate, sdch\r\n" \
"Accept-Language: it-IT,it;q=0.8,en-US;q=0.6,en;q=0.4\r\n\r\n";


void test_GetTemp() {
    test_InitWebServer();
    addString(GET_temp);
    
    temp=10;
    
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    
    addAction("AT+CIPSEND=0,18\r\n", putSendChar);
    addAction("HTTP/1.1 200  OK\r\n", putSendOK);
    addAction("AT+CIPSEND=0,16\r\n", putSendChar);
    addAction("Content-Length: 2\r\n", putSendOK);
    addAction("AT+CIPSEND=0,4\r\n", putSendChar);
    addAction("10\r\n", putSendOK);
    addAction("AT+CIPSEND=0,2\r\n", putSendChar);
    addAction("\r\n", putSendOK);
 
    workWebServer();
}

const char  GET_threshold[] = "+IPD,0,425:"\
"GET /threshold HTTP/1.1\r\n" \
"Host: 127.0.0.1\r\n" \
"Connection: keep-alive\r\n" \
"Cache-Control: max-age=0\r\n"  \
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n" \
"Upgrade-Insecure-Requests: 1\r\n" \
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36\r\n" \
"Accept-Encoding: gzip, deflate, sdch\r\n" \
"Accept-Language: it-IT,it;q=0.8,en-US;q=0.6,en;q=0.4\r\n\r\n";


void test_GetThereshold() {
    test_InitWebServer();
    addString(GET_threshold);
    
    threshold=11;
    
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    
    addAction("HTTP/1.1 200  OK\r\n", nullAction);
    addAction("Content-Length: 2\r\n", nullAction);
    addAction("11\r\n", nullAction);
    addAction("\r\n", nullAction);
 
    workWebServer();
}

const char  PUT_ENABLE[] = "+IPD,0,418:"\
"PUT /enable HTTP/1.1\r\n"\
"Host: 127.0.0.1\r\n"\
"Connection: keep-alive\r\n"\
"Cache-Control: max-age=0\r\n"\
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"\
"Upgrade-Insecure-Requests: 1\r\n"\
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36\r\n"\
"Accept-Encoding: gzip, deflate, sdch\r\n"\
"Accept-Language: it-IT,it;q=0.8,en-US;q=0.6,en;q=0.4\r\n\r\n"\
"1\r\n";


void test_SetEnable() {
    test_InitWebServer();
    addString(PUT_ENABLE);
    
    enable=0;
    
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    
    addAction("HTTP/1.1 200  OK\r\n", nullAction);
   
    workWebServer();
    workWebServer();
    
    TEST_ASSERT_EQUAL(1, enable);
}

const char  PUT_DISABLE[] = "+IPD,0,418:"\
"PUT /enable HTTP/1.1\r\n"\
"Host: 127.0.0.1\r\n"\
"Connection: keep-alive\r\n"\
"Cache-Control: max-age=0\r\n"\
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"\
"Upgrade-Insecure-Requests: 1\r\n"\
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36\r\n"\
"Accept-Encoding: gzip, deflate, sdch\r\n"\
"Accept-Language: it-IT,it;q=0.8,en-US;q=0.6,en;q=0.4\r\n\r\n"\
"0\r\n";

void test_SetDisable() {
    test_InitWebServer();
    addString(PUT_DISABLE);
    
    enable=1;
    
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    
    addAction("HTTP/1.1 200  OK\r\n", nullAction);
   
    workWebServer();
    workWebServer();
    
    TEST_ASSERT_EQUAL(0, enable);
}

const char  PUT_THRESHOLD[] = "+IPD,0,423:"\
"PUT /threshold HTTP/1.1\r\n"\
"Host: 127.0.0.1\r\n"\
"Connection: keep-alive\r\n"\
"Cache-Control: max-age=0\r\n"\
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"\
"Upgrade-Insecure-Requests: 1\r\n"\
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36\r\n"\
"Accept-Encoding: gzip, deflate, sdch\r\n"\
"Accept-Language: it-IT,it;q=0.8,en-US;q=0.6,en;q=0.4\r\n\r\n"\
"200\r\n";

void test_SetThreshold() {
    test_InitWebServer();
    addString(PUT_THRESHOLD);
    
    threshold=1;
    
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    
    addAction("HTTP/1.1 200  OK\r\n", nullAction);
   
    workWebServer();
    workWebServer();
    
    TEST_ASSERT_EQUAL(200, threshold);
}

const char  GET_WhoAreYou[] = "+IPD,0,432:"\
"GET /who_are_you HTTP/1.1\r\n"\
"Host: 127.0.0.1\r\n" \
"Connection: keep-alive\r\n" \
"Cache-Control: max-age=0\r\n"  \
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n" \
"Upgrade-Insecure-Requests: 1\r\n" \
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36\r\n" \
"Accept-Encoding: gzip, deflate, sdch\r\n" \
"Accept-Language: it-IT,it;q=0.8,en-US;q=0.6,en;q=0.4\r\n\r\n";


void test_who_are_you() {
    test_InitWebServer();
    addString(GET_WhoAreYou);
    
    temp=10;
    
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    
    addAction("HTTP/1.1 200  OK\r\n", nullAction);
    addAction("Content-Length: 21\r\n", nullAction);
    addAction("I am Oven version 1.0\r\n", nullAction);
    addAction("\r\n", nullAction);
 
    workWebServer();
}

const char  ERROR_METHOD[] = "+IPD,0,435:"\
"GET /methodNotExist HTTP/1.1\r\n"\
"Host: 127.0.0.1\r\n" \
"Connection: keep-alive\r\n" \
"Cache-Control: max-age=0\r\n"  \
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n" \
"Upgrade-Insecure-Requests: 1\r\n" \
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36\r\n" \
"Accept-Encoding: gzip, deflate, sdch\r\n" \
"Accept-Language: it-IT,it;q=0.8,en-US;q=0.6,en;q=0.4\r\n\r\n";


void test_methodNotFound(void) {
    test_InitWebServer();
    addString(ERROR_METHOD);
    
    temp=10;
    
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    workWebServer();
    
    addAction("HHTTP/1.1 404 Request not found\r\n\r\n", nullAction);
     
    workWebServer();
}

void runTest(void) {
    RUN_TEST(test_firstData);
    RUN_TEST(test_readDataAfterData);
    RUN_TEST(test_roundInsert);
    RUN_TEST(test_get1Line);
    RUN_TEST(test_get2Lines);
    RUN_TEST(test_foundLineRound);
    RUN_TEST(test_lineNotFound);
    RUN_TEST(test_InitWebServer);
    RUN_TEST(test_simpleIPDData);
    RUN_TEST(test_IPDDataWithPreviousResponse);
    RUN_TEST(test_twoIPData);
    RUN_TEST(test_IPDroundPayload);
    RUN_TEST(test_IPDroundLenPayload);
    RUN_TEST(test_IPDroundChannel);
    RUN_TEST(test_IPDroundHeader);
    RUN_TEST(test_GetTemp);
//    RUN_TEST(test_GetThereshold);
//    RUN_TEST(test_SetEnable);
//    RUN_TEST(test_SetDisable);
//    RUN_TEST(test_SetThreshold);
//    RUN_TEST(test_who_are_you);
//    RUN_TEST(test_methodNotFound);
}

