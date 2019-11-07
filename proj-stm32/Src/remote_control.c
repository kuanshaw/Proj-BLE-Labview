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
	
	blue_t_send_cmd("AT+ROLE=0");				/* ����Ϊ��ģʽ */
	
	sprintf((char*)p,"AT+NAME=\"%s\"", name);
	blue_t_send_cmd(p);
	
//	sprintf((char*)p,"AT+UART=38400,0,0");
//	blue_t_send_cmd(p);
//	
	sprintf((char*)p,"AT+PSWD=%s", password);
	blue_t_send_cmd(p);
	
	blue_t_reset();
	
	myfree(SRAMIN, p);
	
	/* ��������״ֵ̬�����г�ʼ�� */
	my_blue.key_state = not_pressed;			/* ����δ������ */
	my_blue.state = connected;						/* ����״̬ */
	my_blue.led_counter = 0;							/* led����ֵ������LED��˸ */
	my_blue.key_lock = 0;									/* �û���������1 - δ�������û���ʹ�ð�����
																					 0 - �������û�����ʹ�� */
	
	blue_t_reset();				/* Ӳ���ϵĸ�λ������-��ʱ-���� */
}


/* �ڶ�ʱ���ж��б����ã�100ms����һ�� */
void blue_t_update(void)
{
	sys_led_flashing();		/* ϵͳLEDָʾ����˸������LED���������������� */
	
	/* ����״̬ */
	
	/* �������״̬ʱ�����ӣ�ע��������Ҫ��λ���򿪴���֮��������� */
	/* �������� */
	if(BLUE_T_STATE == 1){
		my_blue.state = connected;			/* ״̬�ı� */
		my_blue.key_lock = 0;						/* �����������û�����ʹ�� */
	} 
	/* ����δ���� */
	else if(BLUE_T_STATE == 0){
		my_blue.state = not_connected;		/* ״̬���� */
		my_blue.key_lock = 1;							/* ������������ʱ���������� */
		
		blue_t_led_flashing();					/* ����LED��˸��������ʱδ���� */
	}
	

}

  


/* end of file */
