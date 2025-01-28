/**
  ******************************************************************************
  * @file           : loop.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/20
  ******************************************************************************
  */
#include "bsp_system.h"
/**
  * @brief  loop
  * @note   os_loop
  * @param  None
  * @retval None
  */
void loop(void){
    myGpio_init();
    myUart_init();
    myButton_init();
    myAdc_init();
    myGui_init();
    myTimeIR_init();
    scheduler_init();
    while(1){
        scheduler_run();
    }
}

void os_200hz_task(void){
    os_Button_5ms();//因为按键要求中断触发，所以200hz任务放在中断里面
}

void task_debug(void){
//    // 波形显示
//    MY_LOG(& huart1,"f12.14*");
//    MY_LOG(& huart1,"s11.14*");
//    MY_LOG(& huart1,"t9.14*");
//    // adc打印
//    MY_LOG(& huart1,"%.1f \r\n",rotary_channels[0].adc_value);
}