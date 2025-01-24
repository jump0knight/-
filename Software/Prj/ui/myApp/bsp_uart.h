/**
  ******************************************************************************
  * @file           : bsp_uart.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/24
  ******************************************************************************
  */

#ifndef UI_BSP_UART_H
#define UI_BSP_UART_H

#include "bsp_system.h"

enum{
    UART_TX_IS_WORK = 0,
    UART_TX_IS_DONE ,
};

#define USE_PRINT_DMA 1
#if USE_PRINT_DMA
    #define printf MY_LOG
    int MY_LOG(UART_HandleTypeDef *huart,const char *format,...);
#else
//    #define printf(...) \#ifdef __GNUC__
//    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//    #else
//    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//    #endif
//
//    PUTCHAR_PROTOTYPE
//    {
//        HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, 10);
//        return ch;
//    }
#endif

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

extern uint8_t uart_rx_dma_buffer[128];//接收缓存

void myUart_init(void);
void task_uart_proc(void);

void HAL_UART1_RX_Callback(void);

#endif //UI_BSP_UART_H
