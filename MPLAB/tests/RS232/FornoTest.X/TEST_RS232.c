#include <stdint.h>
#include <xc.h>
#include <stdlib.h>
#include <string.h>

#include "RS232.h"
#include "unity.h"


static const char str1[] = "first data ";
static const char str2[] = "second data ";
static const char str_20bytes[] = "01234567890123456789";
static char buffer[100];

void addString(const char * str){
    while (*str != 0){
        addRS232Char(*str);
        str++;
    }
}

void addLine(const char * str){
    while (*str != 0){
        addRS232Char(*str);
        str++;
    }
    addRS232Char('\r');
    addRS232Char('\n');
}

void  test_firstData(void){
    resetRS232();
    volatile uint8_t * inBuffer = rs232_getInBuffer();
    addString(str1);
    int len = sizeof(str1)-1;
    TEST_ASSERT_EQUAL(len, getRS232ReadSize());
    getRS232ReadData(buffer, len);
    TEST_ASSERT_EQUAL_STRING(str1, buffer );
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void  test_readDataAfterData(void){
    resetRS232();
    volatile uint8_t * inBuffer = rs232_getInBuffer();
    addString(str1);
    getRS232ReadData(buffer, 5);
    buffer[5]=0;
    TEST_ASSERT_EQUAL_STRING("first",buffer );
    TEST_ASSERT_EQUAL(6, getRS232ReadSize());
    getRS232ReadData(buffer, 6);
    buffer[6]=0;
    TEST_ASSERT_EQUAL_STRING(" data ",buffer );
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_roundInsert(void){
    resetRS232();
    for(uint16_t i=0; i < 500; i++){
        addRS232Char('a');
    }
    for(uint16_t i=0; i < 5; i++){
        getRS232ReadData(buffer, 100);
    }
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
    addString(str_20bytes);
    TEST_ASSERT_EQUAL(20, getRS232ReadSize());
    getRS232ReadData(buffer, 20);
    buffer[20]=0;
    TEST_ASSERT_EQUAL_STRING(str_20bytes,buffer );
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_get1Line(void){
    resetRS232();
    addLine(str1);
    int len = sizeof(str1)-1;
    TEST_ASSERT_EQUAL(len+2, getRS232ReadSize());
    TEST_ASSERT_EQUAL(1,getLine(buffer));
    TEST_ASSERT_EQUAL_STRING(str1, buffer );
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_get2Lines(void){
    resetRS232();
    addLine(str1);
    addLine(str2);
    int len = sizeof(str1)+sizeof(str2)-1 -1;
    TEST_ASSERT_EQUAL(len+4, getRS232ReadSize());
    TEST_ASSERT_EQUAL(1,getLine(buffer));
    TEST_ASSERT_EQUAL_STRING(str1, buffer );
    TEST_ASSERT_EQUAL(1,getLine(buffer));
    TEST_ASSERT_EQUAL_STRING(str2, buffer );
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}

void test_foundLineRound(void){
    resetRS232();
    for(uint16_t i=0; i < 500; i++){
        addRS232Char('a');
    }
    for(uint16_t i=0; i < 5; i++){
        getRS232ReadData(buffer, 100);
    }
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
    addLine(str_20bytes);
    TEST_ASSERT_EQUAL(22, getRS232ReadSize());
    TEST_ASSERT_EQUAL(1,getLine(buffer));
    TEST_ASSERT_EQUAL_STRING(str_20bytes,buffer );
    TEST_ASSERT_EQUAL(0, getRS232ReadSize());
}


void test_lineNotFound(void){
    resetRS232();
    addString(str1);
    TEST_ASSERT_EQUAL(0,getLine(buffer));
}



void runTest(void){
    test_firstData();
    test_readDataAfterData();
    test_roundInsert();
    test_get1Line();
    test_get2Lines();
    test_foundLineRound();
    test_lineNotFound();
}
