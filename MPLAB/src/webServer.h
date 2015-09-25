/* 
 * File:   webServer.h
 * Author: paolo
 *
 * Created on 22 agosto 2015, 8.23
 */

#ifndef WEBSERVER_H
#define	WEBSERVER_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void initWebServer();
    void workWebServer();
    
    uint8_t isWebServerOn(void);



#ifdef	__cplusplus
}
#endif

#endif	/* WEBSERVER_H */

