#include "tim.h"

#include "remote_control.h"			/* 无线控制的头文件，即蓝牙 */

TIM_HandleTypeDef htim2;				/* 使用定时器2，100ms产生一次中断 */
																/* 使用72MHz时钟，7200*1000/75M = 0.1s = 100ms */

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200-1;			/* 重装载值 */
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000-1;					/* 分频值 */
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;		/* 时钟计数方向，累加 */
  HAL_TIM_Base_Init(&htim2);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;		/* 内部时钟源 */
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM2)
  {
    __TIM2_CLK_ENABLE();

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }
}


void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM2)
  {
    /* Peripheral clock disable */
    __TIM2_CLK_DISABLE();

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM2_IRQn);

  }
} 

/* 定时器中断回调函数 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	
	if(htim==(&htim2)){
		blue_t_update();
	}
}
