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
void loop(void)
{
    myGpio_init();
    myUart_init();
    mybutton_init();
    myGui_init();
    myTimeIR_init();
    scheduler_init();
    while(1)
    {
        scheduler_run();
    }
}

void os_200hz_task(void)
{
    button_ticks();//因为按键要求中断触发，所以200hz任务放在中断里面
}