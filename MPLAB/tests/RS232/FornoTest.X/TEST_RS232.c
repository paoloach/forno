#include <stdint.h>
#include <xc.h>
#include <stdlib.h>
#include <string.h>

#include "RS232.h"
#include "webServer.h"
#include "unity.h"

uint16_t localTemp;
uint16_t thereshold;
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

void test_simpleIPDData() {
    addString("+IPD,0,14:line1\r\nline2\r\n");
    TEST_ASSERT(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 0);
}

void test_IPDDataWithPreviousResponse() {
    addString("LINK OK\r\n+IPD,0,14:line1\r\nline2\r\n");
    TEST_ASSERT(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 0);
}

void test_twoData() {
    addString("+IPD,0,14:line1\r\nline2\r\n");
    addString("+IPD,0,14:line4\r\nline3\r\n");
    TEST_ASSERT(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line1", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line2", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line3", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 1);
    TEST_ASSERT_EQUAL_STRING("line4", buffer);
    TEST_ASSERT_EQUAL(getIPDLine(buffer), 0);
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
    RUN_TEST(test_twoData);
}
