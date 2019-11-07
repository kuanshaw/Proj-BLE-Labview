#ifndef __LED_H
#define __LED_H

#include "stm32f1xx_hal.h"
#include "remote_control.h"

#define SYS_LED_FLASHING_TIME			500		/* LED 500ms��תһ�Σ�ʹ�ö�ʱ��Ϊ100ms����5�κ���з�ת */
#define SYS_LED_FLASHING_COUNTER 	((u16)(SYS_LED_FLASHING_TIME/TIM2_OVERFLOW_TIME_MS))		/* 5�� */

void sys_led_on(void);
void sys_led_off(void);
void sys_led_flashing(void);
void blue_t_led_on(void);
void blue_t_led_off(void);
void blue_t_led_flashing(void);




#endif 
