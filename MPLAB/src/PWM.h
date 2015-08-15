/* 
 * File:   PWM.h
 * Author: paolo
 *
 * Created on 13 agosto 2015, 21.17
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initPWM(void);
    
    void enableOut(void);
    void disableOut(void);


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

