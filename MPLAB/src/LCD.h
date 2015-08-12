/* 
 * File:   LCD.h
 * Author: paolo
 *
 * Created on 20 marzo 2015, 0.53
 */

#ifndef __LCD__H_
#define __LCD__H_

void initLCD(void);
void line1(void);
void line2(void);
void writeLCD(const char * str);
void writeDataLCD(char data);
#endif