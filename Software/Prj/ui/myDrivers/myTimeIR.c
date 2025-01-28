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
#include "pageGui_volt.h"
double sine_wave[94];
/**
  * @brief  HAL_TIM_PeriodElapsedCallback
  * @note   定时器中断回调函数
  * @param  None
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    static uint8_t flag = 0;
    static uint16_t time_100ms = 0;
    static uint16_t sampling_time =  0;
    static double wave[30];
    if(htim->Instance == TIM14){//1ms
        if(++flag >= 5){
            flag = 0;
            os_200hz_task();
        }
        if(++time_100ms >= 30){
            time_100ms = 0;
            double time = (double) sampling_time/ 30   ;  // 当前时间点
            wave[sampling_time] = 1.65 * (sin(2 * 3.14 * 1   * time) + 1);  // 缩放正弦波到0到3.3V
            sine_wave[volt.wave_index] = wave[sampling_time];
            if(++sampling_time >= 30) sampling_time = 0;

            if(++volt.wave_index >= 94)volt.wave_index = 0;
        }
    }

}

/**
  * @brief  myTimeIR_init
  * @note   定时器中断初始化
  * @param  None
  * @retval None
  */
void myTimeIR_init(void){
    HAL_TIM_Base_Start_IT(&htim14);//200hz 1ms初始化
}
