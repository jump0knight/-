/**
  ******************************************************************************
  * @file           : bsp_uart.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/24
  ******************************************************************************
  */
#include "bsp_uart.h"
#include "stdarg.h"
#include "stdio.h"
#include "stm32h7xx_hal_uart.h"
#include "myStreamParser.h"
/******************************
 *
 *  以下是 串口 + DMA 的 串口 发送 TX buffer
 *
 * ***************************/
volatile uint8_t  usart_dma_tx_over = UART_TX_IS_DONE;
/**
  * @brief  MY_LOG
  * @note   重定义 printf 为DMA发送
  * @param  None
  * @retval None
  */
int MY_LOG(UART_HandleTypeDef *huart,const char *format,...){
    va_list arg;
    static char SendBuff[128] = {0};
    int length;
    while(!usart_dma_tx_over);//等待前一次DMA发送完成

    va_start(arg,format);
    length = vsnprintf((char*)SendBuff,sizeof(SendBuff)+1,(char*)format,arg);
    va_end(arg);

    if(HAL_UART_Transmit_DMA(huart,(uint8_t *)SendBuff,length) != HAL_OK) return -1;//发送失败
    usart_dma_tx_over = UART_TX_IS_WORK;//清0全局标志，发送完成后重新置1
    return length;
}
/**
  * @brief  HAL_UART_TxCpltCallback
  * @note   串口发送完成 回调函数
  * @param  None
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
    if(huart->Instance==USART1){
        usart_dma_tx_over = UART_TX_IS_DONE;
    }
}
/******************************
 *
 *  以下是 串口 + DMA +空闲中断 + 环形缓冲区 的 串口 接受 RX buffer
 *
 * ***************************/
uint8_t uart_rx_dma_buffer[128] = {0};//接收缓存

#define BUUFER_SIZE 64
// 定义环形缓冲区和接收缓冲区
ringbuffer_t usart_ringbuffer;
uint8_t usart_read_buffer[BUUFER_SIZE];

/**
  * @brief  HAL_UART1_RX_Callback 串口1 接受回调函数
  * @note   当 RX 线上 超过一个字节时间没有数据接收，触发 空闲中断（IDLE）。
            调用 USARTx_IRQHandler 并调用 HAL_UART1_RX_Callback
  * @param  None
  * @retval None
  */
void HAL_UART1_RX_Callback(void){
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_dma_buffer, sizeof(uart_rx_dma_buffer));// 启动 DMA 接收
    __HAL_DMA_DISABLE_IT(&hdma_usart1_rx ,DMA_IT_HT);// 禁用半满中断,
}
/**
  * @brief  HAL_UARTEx_RxEventCallback
  * @note   在 USARTx_IRQHandler 中调用 HAL_UART_IRQHandler。
            HAL 库检测到 IDLE 中断，触发回调函数 HAL_UARTEx_RxEventCallback。
  * @note   计算接收到的数据长度。
            将 DMA 缓冲区的数据拷贝到 环形缓冲区。
            清空 DMA 缓冲区，准备下一次接收。
  * @retval None
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    if(huart->Instance == USART1){
        if (!ringbuffer_is_full(&usart_ringbuffer)){//如果环形缓冲区未满
            // 将DMA缓冲区中的数据写入环形缓冲区
            ringbuffer_write(&usart_ringbuffer, uart_rx_dma_buffer, Size);
        }
        memset(uart_rx_dma_buffer, 0, sizeof(uart_rx_dma_buffer));// 清空DMA缓冲区
    }
}

/**
 * @brief  task_uart_proc
 * @note   处理UART接收缓冲区中的数据。
 *         如果在100ms内没有接收到新的数据，将清空缓冲区。
 * @param  None
 * @retval None
 */
// 处理UART接收缓冲区中的数据
void task_uart_proc(void){
    uint8_t data_length = usart_ringbuffer.itemCount;
    // 如果环形缓冲区为空，直接返回
    if(ringbuffer_is_empty(&usart_ringbuffer)) return;
    // 如果数据为空，直接返回
    if (data_length == 0) return;
    // 从环形缓冲区读取数据到读取缓冲区
    ringbuffer_read(&usart_ringbuffer, usart_read_buffer, data_length);
    // 打印读取缓冲区中的数据
    /************** 以下 解析 串口 数据流 ******************************/
    // 遍历 usart_read_buffer，逐字节调用 SParser_Parse 进行解析
    for (uint8_t i = 0; i < data_length; i++) {
        // 单字节传递给解析器
        if (SParser_Parse(&parser, databuff, usart_read_buffer[i]) != HAL_OK){
            // 如果解析到有效完整帧 (SParser_Parse 返回 1)，提取数据
            // 假设 databuff 是解析器中存储解析完字段的结构体
            MY_LOG(& huart1,"data1 : %.1f   \n", databuff[0].flt );
            MY_LOG(& huart1,"data2 : %.1f   \n", databuff[1].flt );
            MY_LOG(& huart1,"data3 : %d     \n", databuff[2].intenger );
            MY_LOG(& huart1,"data4 : %d     \n", databuff[3].intenger );
            //SParser_Init(&parser, "GP", "OE", ",", fmtStr);
        }
    }

    /************** 以上 解析 串口 数据流 ******************************/
//    MY_LOG(& huart1,"ringbuffer data: %s\n", usart_read_buffer);
    // 清空读取缓冲区 usart_read_buffer 是真正的数据
    memset(usart_read_buffer, 0, sizeof(uint8_t) * BUUFER_SIZE);
}

/**
  * @brief  myUart_init
  * @note   串口 DMA 环形缓冲区 初始化
  * @param  None
  * @retval None
  */
void myUart_init(void){
    // 启动 DMA 接收
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_dma_buffer, sizeof(uart_rx_dma_buffer));
    // 禁用半满中断,
    __HAL_DMA_DISABLE_IT(&hdma_usart1_rx ,DMA_IT_HT);
    // 环形缓冲区初始化
    ringbuffer_init(&usart_ringbuffer);
    // 串口解析器初始化
    // 头符号$ 尾符号* 分割符 , 数据类型 f
    SParser_Init(&parser, "$", "*", ",", fmtStr);
}

