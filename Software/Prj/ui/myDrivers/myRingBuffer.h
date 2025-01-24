/**
  ******************************************************************************
  * @file           : myRingBuffer.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/24
  ******************************************************************************
  */

#ifndef UI_MYRINGBUFFER_H
#define UI_MYRINGBUFFER_H

//#include "bsp_system.h"
#include "stdint.h"

#define RINGBUFFER_SIZE (30)

typedef struct {
    uint32_t w;
    uint32_t r;
    uint8_t buffer[RINGBUFFER_SIZE];
    uint32_t itemCount;
}ringbuffer_t;

void ringbuffer_init(ringbuffer_t *rb);
uint8_t ringbuffer_is_full(ringbuffer_t *rb);
uint8_t ringbuffer_is_empty(ringbuffer_t *rb);
int8_t ringbuffer_write(ringbuffer_t *rb, uint8_t *data, uint32_t num);
int8_t ringbuffer_read(ringbuffer_t *rb, uint8_t *data, uint32_t num);

extern ringbuffer_t usart_ringbuffer;

#endif //UI_MYRINGBUFFER_H
