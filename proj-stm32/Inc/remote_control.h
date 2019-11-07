#ifndef __REMOTE_CONTROL_H
#define __REMOTE_CONTROL_H

#include "stm32f1xx_hal.h"

#define CMD_COMMAND (1)			/* 蓝牙触发指令 */
#define BE_CONNECT  (9)			/* 蓝牙保持连接数据帧 */

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
 
 /* GPIO 位带运算 */
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOA_IDR_Addr    (GPIOA_BASE+8)  //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8)  //0x40010C08 

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)
/* end GPIO */

/* User's GPIO */
#define BLUE_T_STATE		PAin(8)					/* 蓝牙状态输入 */
#define BLUE_T_EN				PAout(11)				/* 蓝牙使能位，相当于通断电 */

#define SYS_LED					PCout(13)				/* PC13，系统指示灯 */
#define BLUE_T_LED			PBout(11)				/* 蓝牙状态指示灯 */

#define USER_KEY				PBin(10)				/* 用户按键 */

/* 定时器2产生中断的时间 */
#define TIM2_OVERFLOW_TIME_MS					100

#define BLUE_T_LED_FLASHING_TIME			100		/* LED 100ms反转一次，使用定时器为100ms，则1次后进行反转 */
#define BLUE_T_LED_FLASHING_COUNTER 	((u16)(BLUE_T_LED_FLASHING_TIME/TIM2_OVERFLOW_TIME_MS))		/* 1次 */

/* 蓝牙状态，枚举型 */
typedef enum{
	connected = 0,			/* 蓝牙连接 */
	not_connected = 1,	/* 蓝牙未连接 */
	
} blue_t_state_t;


/* 按键装填，枚举型 */
typedef enum{
	pressed = 0,				/* 按键被按下 */
	not_pressed = 1,		/* 按键未被按下 */
	
} key_state_t;


/* 蓝牙状态结构体 */
typedef struct {
	blue_t_state_t state;			/* 蓝牙连接状态 */
	key_state_t key_state;		/* 按键状态 */
		
	u16 led_counter;					/* LED的计数值 */
	u8 key_lock;							/* 按键锁 */
	
} blue_t_t;


extern blue_t_t my_blue;

u8 blue_t_send_cmd(u8 *cmd);
void blue_t_reset(void);
void blue_t_init(u8 *name, u8 *password);
void blue_t_update(void);


#endif /* __REMOTE_CONTROL_H */ 

