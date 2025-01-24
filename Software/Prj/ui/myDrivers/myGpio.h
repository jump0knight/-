/**
  ******************************************************************************
  * @file           : myGpio.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/20
  ******************************************************************************
  */

#ifndef INC_002_G_MYGPIO_H
#define INC_002_G_MYGPIO_H
#include "bsp_system.h"
typedef enum {
    GPIO_LOW = 0,  // 低电平点亮
    GPIO_HIGH = 1  // 高电平点亮
} GPIO_Level;

typedef struct                   //结构体对齐
{
    GPIO_TypeDef *port;          // 4字节或8字节（根据指针大小）- 端口地址放在首位
    uint32_t pin;                // 4字节 - GPIO引脚号
    uint32_t period;             // 4字节 - 闪烁周期
    uint16_t times ;              // 2字节 - 预设闪烁总次数
    uint16_t cnt ;                // 2字节 - 闪烁控制计数器
    uint16_t times_cnt ;          // 2字节 - 记录已闪烁次数
    uint8_t reset ;               // 1字节 - 闪烁进程复位标志
    uint8_t end ;                 // 1字节 - 闪烁完成标志位
    float light_on_percent ;      // 4字节 - 单个周期内点亮时间百分比
    GPIO_Level level;            // 点亮电平类型，高电平/低电平
} _gpio_control;



void myGpio_init(void);

void led_setup(uint32_t _period, float _light_on_percent, uint16_t _times);
void task_led_proc(void);

#endif //INC_002_G_MYGPIO_H
