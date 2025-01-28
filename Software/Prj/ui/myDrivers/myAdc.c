/**
  ******************************************************************************
  * @file           : myAdc.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/26
  ******************************************************************************
  */
#include "myAdc.h"
#include "adc.h"

/**
  * @brief  power_monitor_read_value
  * @note   返回任意通道的 adc 有效值
  * @param  channel adc 通道
  * @retval None
  */
uint16_t power_monitor_read_value(uint8_t channel)
{
    if(channel > (CHANNEL_SIZE - 1))
        channel = (CHANNEL_SIZE - 1);
    return (uint16_t)rotary_channels[channel].adc_value;
}

// 回调函数声明 旋钮按键
void rotate_right_channel_0(void);
void rotate_left_channel_0(void);
void rotate_right_channel_1(void);
void rotate_left_channel_1(void);
// 定义电位器通道实例
RotaryEncoderChannel_t rotary_channels[2] = {
        { .dma_buffer = {0},
                .adc_value = 0,
                .previous_adc_value = 0,
                .onRotateRight = rotate_right_channel_0,
                .onRotateLeft = rotate_left_channel_0 },

        { .dma_buffer = {0},
                .adc_value = 0,
                .previous_adc_value = 0,
                .onRotateRight = rotate_right_channel_1,
                .onRotateLeft = rotate_left_channel_1 }
};

/**
  * @brief  rotate_right_channel_0 `adc_value[0]` 的右旋回调函数
  **/
__weak void rotate_right_channel_0(void) {

}

/**
  * @brief  rotate_left_channel_0 `adc_value[0]` 的左旋回调函数
  **/
__weak void rotate_left_channel_0(void) {

}

/**
  * @brief  rotate_right_channel_1 `adc_value[1]` 的右旋回调函数
  **/
__weak void rotate_right_channel_1(void) {

}

/**
  * @brief  rotate_left_channel_1 `adc_value[1]` 的左旋回调函数
  **/
__weak void rotate_left_channel_1(void) {

}

/**
  * @brief  检测旋钮方向
  * @param  channel RotaryEncoderChannel_t类型的旋钮通道结构体
  * @note   检测并调用回调
  */
void process_rotary_encoder(RotaryEncoderChannel_t* channel) {
    if (abs(channel->adc_value - channel->previous_adc_value) > ROTARY_THRESHOLD) {
        if (channel->adc_value > channel->previous_adc_value) {
            channel->onRotateLeft(); // 左旋回调
        } else if (channel->adc_value < channel->previous_adc_value) {
            channel->onRotateRight(); // 右旋回调
        }
        // 更新上一轮的ADC值
        channel->previous_adc_value = channel->adc_value;
    }
}
/**
  * @brief  解析ADC采样值并更新对应通道的ADC值
  * @param  channel RotaryEncoderChannel_t类型的旋钮通道结构体
  */
void update_channel_adc_value(RotaryEncoderChannel_t* channel) {
    channel->adc_value = 0;
    for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
        channel->adc_value += channel->dma_buffer[i];
    }
    channel->adc_value /= BUFFER_SIZE; // 求平均值 此时adc数据为原始值
}

/**
  * @brief  task_adc_proc: 处理所有旋钮的采样解析
  * @note   周期性调用该函数，每隔20ms进行解析处理
  */
void task_adc_proc(void) {
    // 更新 channel 0 的 ADC 值
    update_channel_adc_value(&rotary_channels[0]);
//    //更新 channel 1 的 ADC 值
//    update_channel_adc_value(&rotary_channels[1]);
//    //周期性调用该函数，用于检测旋钮变化并处理回调
//    process_rotary_encoder(&rotary_channels[0]);
//    process_rotary_encoder(&rotary_channels[1]);
}

/**
  * @brief  myAdc_init: 初始化ADC和旋钮结构体
  * @note   在系统启动时调用
  */
void myAdc_init(void) {
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)rotary_channels[0].dma_buffer, BUFFER_SIZE);
//    HAL_ADC_Start_DMA(&hadc2, (uint32_t*)rotary_channels[1].dma_buffer, 30);
    task_adc_proc();
    // 启动时先进行一次解析，初始化 previous 值
    rotary_channels[0].previous_adc_value = rotary_channels[0].adc_value;
//    rotary_channels[1].previous_adc_value = rotary_channels[1].adc_value;
}

