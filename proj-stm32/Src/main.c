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

	delay_init(72);     /* 使用嘀嗒定时器来进行延时，使用72MHz的时钟 */
	HAL_UART_Receive_IT(&huart1, (u8 *)aRxBuffer, RXBUFFERSIZE);   /* 打开串口接收中断 */
	HAL_TIM_Base_Start_IT(&htim2);     /* 打开定时器重载中断 */

  /* Infinite loop */

	/* 蓝牙初始化函数 */
	/* 修改蓝牙名称以及配对码，不可用，需要按住蓝牙按键上电，配置为AT模式后才能成功配置 */
	blue_t_init("Ji_BlueTeeth", "4321");
	
  while (1)
  {
		/* 用户的按键已上锁，此时LED跟随按键按下而亮，松开而暗 */
		if(my_blue.key_lock == 0) {
			blue_t_led_off();		/* 将蓝牙指示LED关闭 */
			
			/* 按键扫描 */
			if(USER_KEY == 0) {
				delay_ms(50);				/* 延时，消除按键抖动*/
				if(USER_KEY == 0){
					my_blue.key_state = pressed;			/* 改变按键状态，在更新函数中处理 */
					printf("%d\r\n", CMD_COMMAND);		/* 按键被按下，即发送指令，指令在宏定义中给出 */
					blue_t_led_on();									/* 点亮LED */
					
					while(1){							/* 松手检测，按键不松开将一直停在这里，但定时器仍旧在工作 */
						if(USER_KEY == 1) {
							blue_t_led_off();	/* 松开，LED灭 */
							break;		/* 直到检测到按键松开则跳出循环 */
						}
					}
				}
			} /* Key be pressed */
			else
			{
				printf("%d\r\n", BE_CONNECT); 		/* 发送保持连接的数据帧，避免蓝牙自动断开 */
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
