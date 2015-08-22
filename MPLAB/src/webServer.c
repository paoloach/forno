#include "webServer.h"
#include "RS232.h"
#include <string.h>

static char buffer[256];

void initWebServer() {

}

void workWebServer() {
    if (getLine(buffer)==1){
        if (strcmp(buffer,"GET ")==1){
            sendRS232("getting GET request\r\n");
        }
    }
}
