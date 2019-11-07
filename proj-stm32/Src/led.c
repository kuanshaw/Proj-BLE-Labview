#include "led.h"

/* 系统指示LED */
u16 sys_led_counter = 0;

void sys_led_on(void)
{
	SYS_LED = 1;
}

void sys_led_off(void)
{
	SYS_LED = 0;
}

void sys_led_flashing(void)
{
	static u8 flag = 1;
	sys_led_counter++;
	
	/* 大于指定值则实现LED灯的反转 */
	if(sys_led_counter > SYS_LED_FLASHING_COUNTER ){
		if(flag == 1){
			sys_led_on();
			flag = 0;
		} else if(flag == 0){
			sys_led_off();
			flag = 1;
		}
		
		sys_led_counter = 0;		/* 清空 */
	}
}


/* 蓝牙指示LED */
void blue_t_led_on(void)
{
	BLUE_T_LED = 1;
}

void blue_t_led_off(void)
{
	BLUE_T_LED = 0;
}

void blue_t_led_flashing(void)
{
	static u8 flag = 1;
	
	my_blue.led_counter++;		/* 计数值加一 */
	
	/* 大于指定值则实现LED灯的反转 */
	if(my_blue.led_counter > BLUE_T_LED_FLASHING_COUNTER ){		
		if(flag == 1){
			blue_t_led_on();
			flag = 0;
		} else if(flag == 0){
			blue_t_led_off();
			flag = 1;
		}
		
		my_blue.led_counter = 0; 	/* 清空计数值 */
	}
}



/* end of flie */
