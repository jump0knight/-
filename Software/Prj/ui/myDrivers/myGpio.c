/**
  ******************************************************************************
  * @file           : myGpio.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/20
  ******************************************************************************
  */
#include "myGpio.h"

_gpio_control  led;
/*********************************************************************
 * @fn      nGpio_init
 *
 * @brief   实现gpio端口结构体初始化
 *
 * @return  none
 */
void myGpio_init(void){
        led.port = GPIOA;  // All LEDs connected to GPIOC
        led.pin = GPIO_PIN_1;  // PC8 to PC15 (pins 8 to 15)
        led.level = GPIO_LOW;//Low light the gpio
        led.period = 40;   // 200 ms cycle, 40 * 5 ms
        led.light_on_percent = 0.5f;  // 50% ON time for even LEDs
        led.times = 5;
        led.reset = 1;
}
/*********************************************************************
 * @fn      gpio_control_work(_gpio_control *light)
 * @time    5ms
 * @brief   gpio驱动状态机
 * @input   _gpio_control *light-gpio控制结构体
 * @return  none
 */
void gpio_control_work(_gpio_control *light){
    if(light->reset==1){                                    //重置gpio控制
        light->reset=0;
        light->cnt=0;
        light->times_cnt=0;
        light->end=0;
    }
    if(light->times_cnt>=light->times){                     //gpio周期控制
        light->end=1;
        if (light->level == GPIO_HIGH) {
            GPIO_CONTROL_LOW(light->port, light->pin);// 低电平点亮
        } else {
            GPIO_CONTROL_HIGH(light->port, light->pin);// 高电平点亮
        }
        return;
    }
    light->cnt++;                                           //5ms
    if(light->cnt<=light->period*light->light_on_percent){  // 在点亮时间区间内（根据 light_on_percent）

        if (light->level == GPIO_HIGH) {
            GPIO_CONTROL_HIGH(light->port, light->pin);// 高电平点亮
        } else {
            GPIO_CONTROL_LOW(light->port, light->pin);// 低电平点亮
        }
    }else if(light->cnt<light->period){                     // 在熄灭时间区间内
        if (light->level == GPIO_HIGH) {
            GPIO_CONTROL_LOW(light->port, light->pin);// 低电平点亮
        } else {
            GPIO_CONTROL_HIGH(light->port, light->pin);// 高电平点亮
        }
    }else{//周期结束，重置计数并记录已完成次数
        light->cnt=0;
        light->times_cnt++;
    }
}
/*********************************************************************
 * @fn      led_setup
 * @time
 * @brief   led及时控制 (Dynamically control LED configuration)
 * @input   uint32_t _period, float _light_on_percent, uint16_t _times
 * @return  none
 */
void led_setup(uint32_t _period, float _light_on_percent, uint16_t _times){
    led.period = _period;
    led.light_on_percent = _light_on_percent;
    led.reset = 1;
    led.times = _times;
}
/*********************************************************************
 * @fn      task_led_proc
 * @time    5ms
 * @brief   led任务函数 (Handle the LED control for all 8 LEDs)
 *
 * @return  none
 */
void task_led_proc(void){
    // Loop through  1 BUZZER
    gpio_control_work(&led);
}