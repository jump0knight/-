/**
  ******************************************************************************
  * @file           : myTimeIR.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/24
  ******************************************************************************
  */
#include "myTimeIR.h"
#include "tim.h"

/**
  * @brief  HAL_TIM_PeriodElapsedCallback
  * @note   定时器中断回调函数
  * @param  None
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint8_t flag = 0;
    if(htim->Instance == TIM14)//1ms
    {
        if(++flag >= 5){
            flag = 0;
            os_200hz_task();
        }
    }
}

/**
  * @brief  myTimeIR_init
  * @note   定时器中断初始化
  * @param  None
  * @retval None
  */
void myTimeIR_init(void)
{
    HAL_TIM_Base_Start_IT(&htim14);//200hz 5ms初始化
}
