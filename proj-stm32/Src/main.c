/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "remote_control.h"
#include "led.h"
#include "delay.h"

void SystemClock_Config(void);

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();

	delay_init(72);     /* ʹ����શ�ʱ����������ʱ��ʹ��72MHz��ʱ�� */
	HAL_UART_Receive_IT(&huart1, (u8 *)aRxBuffer, RXBUFFERSIZE);   /* �򿪴��ڽ����ж� */
	HAL_TIM_Base_Start_IT(&htim2);     /* �򿪶�ʱ�������ж� */

  /* Infinite loop */

	/* ������ʼ������ */
	/* �޸����������Լ�����룬�����ã���Ҫ��ס���������ϵ磬����ΪATģʽ����ܳɹ����� */
	blue_t_init("Ji_BlueTeeth", "4321");
	
  while (1)
  {
		/* �û��İ�������������ʱLED���水�����¶������ɿ����� */
		if(my_blue.key_lock == 0) {
			blue_t_led_off();		/* ������ָʾLED�ر� */
			
			/* ����ɨ�� */
			if(USER_KEY == 0) {
				delay_ms(50);				/* ��ʱ��������������*/
				if(USER_KEY == 0){
					my_blue.key_state = pressed;			/* �ı䰴��״̬���ڸ��º����д��� */
					printf("%d\r\n", CMD_COMMAND);		/* ���������£�������ָ�ָ���ں궨���и��� */
					blue_t_led_on();									/* ����LED */
					
					while(1){							/* ���ּ�⣬�������ɿ���һֱͣ���������ʱ���Ծ��ڹ��� */
						if(USER_KEY == 1) {
							blue_t_led_off();	/* �ɿ���LED�� */
							break;		/* ֱ����⵽�����ɿ�������ѭ�� */
						}
					}
				}
			} /* Key be pressed */
			else
			{
				printf("%d\r\n", BE_CONNECT); 		/* ���ͱ������ӵ�����֡�����������Զ��Ͽ� */
				delay_ms(50);
			}
		} /* lock is not in */
	} /* while */ 
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

}

#endif
