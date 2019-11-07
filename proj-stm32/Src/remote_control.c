#include "remote_control.h"
#include "usart.h"
#include "malloc.h"
#include "string.h" 
#include "led.h"
#include "delay.h"

blue_t_t my_blue;


u8 blue_t_send_cmd(u8 *cmd)
{
	USART_RX_STA=0;
	printf("%s\r\n", cmd);

	return 1;
}

void blue_t_reset(void)
{
	BLUE_T_EN = 0;
	delay_ms(500);
	BLUE_T_EN = 1;
}

void blue_t_init(u8 *name, u8 *password)
{
	u8 *p;
	p = mymalloc(SRAMIN, 100);
	
	blue_t_send_cmd("AT+ROLE=0");				/* 蓝牙为从模式 */
	
	sprintf((char*)p,"AT+NAME=\"%s\"", name);
	blue_t_send_cmd(p);
	
//	sprintf((char*)p,"AT+UART=38400,0,0");
//	blue_t_send_cmd(p);
//	
	sprintf((char*)p,"AT+PSWD=%s", password);
	blue_t_send_cmd(p);
	
	blue_t_reset();
	
	myfree(SRAMIN, p);
	
	/* 将蓝牙的状态值都进行初始化 */
	my_blue.key_state = not_pressed;			/* 按键未被按下 */
	my_blue.state = connected;						/* 蓝牙状态 */
	my_blue.led_counter = 0;							/* led计数值，用于LED闪烁 */
	my_blue.key_lock = 0;									/* 用户按键锁，1 - 未上锁，用户可使用按键；
																					 0 - 上锁，用户不可使用 */
	
	blue_t_reset();				/* 硬件上的复位，拉高-延时-拉低 */
}


/* 在定时器中断中被调用，100ms跟新一次 */
void blue_t_update(void)
{
	sys_led_flashing();		/* 系统LED指示灯闪烁，板载LED，表明程序在运行 */
	
	/* 更新状态 */
	
	/* 检测蓝牙状态时候连接，注意这里需要上位机打开串口之后才算连接 */
	/* 蓝牙连接 */
	if(BLUE_T_STATE == 1){
		my_blue.state = connected;			/* 状态改变 */
		my_blue.key_lock = 0;						/* 按键解锁，用户可以使用 */
	} 
	/* 蓝牙未连接 */
	else if(BLUE_T_STATE == 0){
		my_blue.state = not_connected;		/* 状态更新 */
		my_blue.key_lock = 1;							/* 按键上锁，此时按键不可用 */
		
		blue_t_led_flashing();					/* 蓝牙LED闪烁，表明此时未连接 */
	}
	

}

  


/* end of file */
