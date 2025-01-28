/**
  ******************************************************************************
  * @file           : myAdc.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/26
  ******************************************************************************
  */

#ifndef UI_MYADC_H
#define UI_MYADC_H

#include "bsp_system.h"
// 设置旋转阈值（灵敏度）//后续可调
#define ROTARY_THRESHOLD (200)

#define BUFFER_SIZE (30)
#define CHANNEL_SIZE (2)
// 封装电位器相关数据结构
typedef struct {
    uint32_t dma_buffer[BUFFER_SIZE];    // DMA采样缓存
    float adc_value;         // 当前ADC采样值
    float previous_adc_value;// 上一次ADC采样值
    void (*onRotateRight)(void); // 右旋回调函数
    void (*onRotateLeft)(void);  // 左旋回调函数
} RotaryEncoderChannel_t;
extern RotaryEncoderChannel_t rotary_channels[CHANNEL_SIZE];

void myAdc_init(void);
void task_adc_proc(void);

uint16_t power_monitor_read_value(uint8_t channel);

#endif //UI_MYADC_H
