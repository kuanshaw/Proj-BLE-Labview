#ifndef __REMOTE_CONTROL_H
#define __REMOTE_CONTROL_H

#include "stm32f1xx_hal.h"

#define CMD_COMMAND (1)			/* ��������ָ�� */
#define BE_CONNECT  (9)			/* ����������������֡ */

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
 
 /* GPIO λ������ */
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
#define BLUE_T_STATE		PAin(8)					/* ����״̬���� */
#define BLUE_T_EN				PAout(11)				/* ����ʹ��λ���൱��ͨ�ϵ� */

#define SYS_LED					PCout(13)				/* PC13��ϵͳָʾ�� */
#define BLUE_T_LED			PBout(11)				/* ����״ָ̬ʾ�� */

#define USER_KEY				PBin(10)				/* �û����� */

/* ��ʱ��2�����жϵ�ʱ�� */
#define TIM2_OVERFLOW_TIME_MS					100

#define BLUE_T_LED_FLASHING_TIME			100		/* LED 100ms��תһ�Σ�ʹ�ö�ʱ��Ϊ100ms����1�κ���з�ת */
#define BLUE_T_LED_FLASHING_COUNTER 	((u16)(BLUE_T_LED_FLASHING_TIME/TIM2_OVERFLOW_TIME_MS))		/* 1�� */

/* ����״̬��ö���� */
typedef enum{
	connected = 0,			/* �������� */
	not_connected = 1,	/* ����δ���� */
	
} blue_t_state_t;


/* ����װ�ö���� */
typedef enum{
	pressed = 0,				/* ���������� */
	not_pressed = 1,		/* ����δ������ */
	
} key_state_t;


/* ����״̬�ṹ�� */
typedef struct {
	blue_t_state_t state;			/* ��������״̬ */
	key_state_t key_state;		/* ����״̬ */
		
	u16 led_counter;					/* LED�ļ���ֵ */
	u8 key_lock;							/* ������ */
	
} blue_t_t;


extern blue_t_t my_blue;

u8 blue_t_send_cmd(u8 *cmd);
void blue_t_reset(void);
void blue_t_init(u8 *name, u8 *password);
void blue_t_update(void);


#endif /* __REMOTE_CONTROL_H */ 

