#include "webServer.h"
#include "RS232.h"
#include <string.h>
#include <stdlib.h>


static char buffer[256];

enum HTTPParserStatus {
    httpRequest,
    httpHeader,
    httpWaitForEndRequest,
    httpElaboratePutBody,
    httpSendResponse
};

enum Resources {
    resNONE,
    resGetTEMPOven,
    resGetTEMPLocal,
    resGetTEMPOven1,
    resGetTEMPOven2,
    resGetThreshold,
    resGetWhoAreYou,
    resSetThreshold,
    resSetEnable
};

enum MethodType {
    methodGET,
    methodPUT,
    methodPOST
};

enum ContentType {
    ctTextPlain,
    ctOther
};

enum HTTPResponse {
    httpOK,
    httpWrongProtocoll,
    httpNotFound,
    httpUnsopportedMediaType
};

extern uint16_t localTemp;
extern uint16_t thereshold;
extern uint16_t tempReal;
extern uint16_t temp1;
extern uint16_t temp2;
extern uint16_t temp;
extern uint8_t enable;

static void manageGET(char * iter);
static void managePUT(char * iter);
static void manageGetTemp(char * iter);
static uint8_t parseRequestLine(char * iter);
static uint8_t rightHTTPVersion(char * iter);
static void checkRequestLine(void);
static void checkHeader(void);
static void checkSendResponse(void);
static void elaboratePutBody(void);
static void setEnable(void);

static void sendWrongProtocol(void);
static void sendNotFound(void);
static void sendOk(void);
static void sendBody(void);

static char * startMethod;
static char * startRequestURI;
static char * startHTTP_Version;
static int16_t contentLenght;
static uint8_t enableWebServer=0;
static enum HTTPParserStatus httpStatus;
static enum Resources resource;
static enum HTTPResponse httpResponse;
static enum ContentType contentType;
static enum MethodType methodType;

uint8_t isWebServerOn(void) {
    return enableWebServer;
}

void initWebServer() {
    static char initBuffer[20];
    static const char respOK[] = "OK";
    static const char string1[] = "AT+CWMODE=3\r\n";
    static const char string2[] = "AT+CIPMUX=1\r\n";
    static const char string3[] = "AT+CIPSERVER=1,8080\r\n";
    httpStatus = httpRequest;
    sendRS232(string1);
    while (getRS232ReadSize() <4);
    enableWebServer=0;
    if (getRS232ReadSize() < 20){
        getLine(initBuffer);
        if (memcmp(initBuffer, respOK, sizeof(respOK)-1)!=0){
            return;
        }
    }
    sendRS232(string2);
    while (getRS232ReadSize() <4);
    if (getRS232ReadSize() < 20){
        getLine(initBuffer);
        if (memcmp(initBuffer, respOK, sizeof(respOK)-1)!=0){
            return;
        }
    }
    sendRS232(string3);
    while (getRS232ReadSize() <4);
    if (getRS232ReadSize() < 20){
        getLine(initBuffer);
        if (memcmp(initBuffer, respOK, sizeof(respOK)-1)!=0){
            return;
        }
    }
    enableWebServer=1;
}

void workWebServer() {
    if (enableWebServer==0){
        return;
    }
    switch (httpStatus) {
        case httpRequest:
            checkRequestLine();
            break;
        case httpHeader:
            checkHeader();
            break;
        case httpWaitForEndRequest:
            if (getLine(buffer) == 1) {
                if (buffer[0] == 0) {
                    httpStatus = httpSendResponse;
                }
            }
            break;
        case httpSendResponse:
            checkSendResponse();
            break;
        case httpElaboratePutBody:
            elaboratePutBody();
            break;
    }
}

static void elaboratePutBody(void) {
    switch (resource) {
        case resSetEnable:
            setEnable();
            break;
        case resSetThreshold:
            break;
        default:
            httpStatus = httpSendResponse;
            httpResponse = httpNotFound;
            break;
    }
}

static void setEnable(void) {
    if (getLine(buffer) == 1) {
        if (buffer[0] == '1' && buffer[1] == 0) {
            enable = 1;
        } else {
            // any other value but '1' is false, that is power off the oven
            enable = 0;
        }
        httpStatus = httpSendResponse;
        httpResponse = httpOK;
    }
}

static void checkSendResponse(void) {
    switch (httpResponse) {
        case httpOK:
            sendOk();
            sendBody();
            break;
        case httpWrongProtocoll:
            sendWrongProtocol();
            break;
        case httpNotFound:
            sendNotFound();
            break;
    }
    httpStatus = httpRequest;
    contentLenght = 0;
    contentType = ctOther;
}

static void checkRequestLine(void) {
    static const char strGET[] = "GET ";
    static const char strPUT[] = "PUT ";
    if (getLine(buffer) == 1) {
        httpResponse = httpWrongProtocoll;
        if (parseRequestLine(buffer)) {
            if (rightHTTPVersion(startHTTP_Version)) {
                httpResponse = httpOK;
                if (memcmp(startMethod, strGET, sizeof (strGET) - 1) == 0) {
                    methodType = methodGET;
                    manageGET(startRequestURI);
                } else if (memcmp(startMethod, strPUT, sizeof (strPUT) - 1) == 0) {
                    methodType = methodPUT;
                    managePUT(startRequestURI);
                } else {
                    httpResponse = httpNotFound;
                }
            } else {
                httpResponse = httpWrongProtocoll;
            }
            httpStatus = httpHeader;
        } else {
            httpStatus = httpRequest;
        }
    }
}

static void checkHeader(void) {
    static const char string1[] = "Content-Type: text/html";
    static const char string2[] = "Content-Length: ";
    if (getLine(buffer) == 1) {
        if (buffer[0] == 0) {
            switch (methodType) {
                case methodPUT:
                    httpStatus = httpElaboratePutBody;
                    break;
                case methodGET:
                    httpStatus = httpSendResponse;
                    break;
                default:
                    httpStatus = httpRequest;
                    break;
            }
        }
        if (memcmp(buffer, string2, sizeof (string2) - 1) == 0) {
            contentLenght = atoi(buffer + sizeof (string2) - 1);
        } else if (memcmp(buffer, string1, sizeof (string1) - 1) == 0) {
            contentType = ctTextPlain;
        }
    }
}

static uint8_t parseRequestLine(char * iter) {
    while (*iter == ' ') {
        iter++;
        if (*iter == 0) {
            return 0;
        }
    }
    startMethod = iter;
    while (*iter != ' ') {
        iter++;
        if (*iter == 0) {
            return 0;
        }
    }
    while (*iter == ' ') {
        iter++;
        if (*iter == 0) {
            return 0;
        }
    }
    startRequestURI = iter;
    while (*iter != ' ') {
        iter++;
        if (*iter == 0) {
            return 0;
        }
    }
    while (*iter == ' ') {
        iter++;
        if (*iter == 0) {
            return 0;
        }
    }
    startHTTP_Version = iter;
    return 1;
}

static uint8_t rightHTTPVersion(char * iter) {
    if (strcmp(iter, "HTTP/1.1") == 0) {
        return 1;
    } else {
        return 0;
    }
}

// /temp/ --> oven temperature
// /temp/oven --> oven temperature
// /temp/oven/1 --> oven temperature sensor 1
// /temp/oven/1 --> oven temperature sensor 2
// /temp/local --> local temperature
// /threshold --> threshold temperature
// /who_are_you --> version

static void manageGET(char * iter) {
    static const char string1 [] = "/temp ";
    static const char string2 [] = "/threshold ";
    static const char string3 [] = "/who_are_you ";
    resource = resNONE;
    if (memcmp(iter, string1, sizeof (string1) - 1) == 0) {
        iter += sizeof (string1) - 1;
        manageGetTemp(iter);
    } else if (memcmp(iter, string2, sizeof (string2) - 1) == 0) {
        iter += sizeof (string2) - 1;
        resource = resGetThreshold;
    } else if (memcmp(iter, string3, sizeof (string3) - 1) == 0) {
        iter += sizeof (string3) - 1;
        resource = resGetWhoAreYou;

    } else {
        resource = resNONE;
    }
}

static void manageGetTemp(char * iter) {
    const char string1[] = "local ";
    const char string2[] = "1 ";
    const char string3[] = "2 ";
    const char string4[] = "oven ";
    if (*iter == ' ') {
        resource = resGetTEMPOven;
    } else {
        if (*iter == '/') {
            iter++;
        } else {
            resource = resNONE;
        }
        if (*iter == ' ') {
            iter++;
            resource = resGetTEMPOven;
        } else if (memcmp(iter, string1, sizeof (string1) - 1) == 0) {
            iter += sizeof (string1) - 1;
            resource = resGetTEMPLocal;
        } else if (memcmp(iter, string2, sizeof (string2) - 1) == 0) {
            iter += sizeof (string2) - 1;
            resource = resGetTEMPOven1;
        } else if (memcmp(iter, string3, sizeof (string3) - 1) == 0) {
            iter += sizeof (string3) - 1;
            resource = resGetTEMPOven2;
        } else if (memcmp(iter, string4, sizeof (string4) - 1) == 0) {
            iter += sizeof (string4) - 1;
            resource = resGetTEMPOven2;
        } else {
            resource = resNONE;
        }
    }
}

static void managePUT(char * iter) {
    const char strThreshold[] = "/threshold ";
    const char strEnable[] = "/enable ";
    resource = resNONE;
    if (memcmp(iter, strThreshold, sizeof (strThreshold) - 1) == 0) {
        iter += sizeof (strThreshold) - 1;
        resource = resSetThreshold;
    } else if (memcmp(iter, strEnable, sizeof (strEnable) - 1) == 0) {
        iter += sizeof (strEnable) - 1;
        resource = resSetEnable;
    } else {
        resource = resNONE;
    }
}

static void sendWrongProtocol(void) {
    sendRS232("HTTP/1.1 400 Bad Request\r\n\r\n");
}

static void sendNotFound(void) {
    sendRS232("HTTP/1.1 40$ Request not found\r\n\r\n");
}

static void sendOk(void) {
    sendRS232("HTTP/1.1 200  OK\r\n\r\n");
}

static void sendBody(void) {
    const char * body;
    char strLen[20];
    switch (resource) {
        case resGetTEMPOven:
            body = itoa(buffer, temp, 10);
            break;
        case resGetTEMPLocal:
            body = itoa(buffer, localTemp, 10);
            break;
        case resGetTEMPOven1:
            body = itoa(buffer, temp1, 10);
            break;
        case resGetTEMPOven2:
            body = itoa(buffer, temp2, 10);
            break;
        case resGetThreshold:
            body = itoa(buffer, thereshold, 10);
            break;
        case resGetWhoAreYou:
            body = "I am Oven version 1.0";
        default:
            body = NULL;
    }
    if (body != NULL) {
        uint8_t len = strlen(body);
        sendRS232("Content-Length: ");
        itoa(strLen, len, 10);
        sendRS232(strLen);
        sendRS232("\r\n");
        sendRS232(body);
        sendRS232("\r\n");
    }
}