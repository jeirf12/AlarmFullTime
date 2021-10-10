/* 
 * @File   Pinout.h
 * @Author jhonfer <jruizf@unicauca.edu.co>
 *
 * Created on 14 September 2021, 16:37
 */

#include <pic18f4550.h>

#ifndef PINOUT_H
#define PINOUT_H

#ifdef __cplusplus
extern "C" {
#endif /* end macro __cplusplus */

#define BUZZER RE0
#define MOTION_DETECTION RB2
#define CNF_SENSOR TRISB2
#define LED_YELLOW LATB6
#define CNF_LED_YELLOW TRISB6

#define ON 1
#define OFF 0

#define INPUT 1
#define OUTPUT 0

#ifdef __cplusplus
}
#endif /* end macro __cplusplus */

#endif /* end macro CONFIG_H */
