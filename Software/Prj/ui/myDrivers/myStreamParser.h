/**
  ******************************************************************************
  * @file           : myStreamParser.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/24
  ******************************************************************************
  */

#ifndef UI_MYSTREAMPARSER_H
#define UI_MYSTREAMPARSER_H

#include "stdint.h"
#include "myRingBuffer.h"
#include "bsp_uart.h"

#define STRING_BUFFER_SIZE 64

// 解析器结构体
typedef struct {
    const char *headStr;
    const char *tailStr;
    const char *divStr;
    const char *typeList;  // 例如 "f" 表示浮点数
    uint8_t state;  // 当前状态
} stream_parser_t;

extern stream_parser_t parser;

void stream_parser_init(stream_parser_t *parser, const char *headStr, const char *tailStr, const char *divStr, const char *typeList);

void parse_stream_data(stream_parser_t *parser, uint8_t *usart_read_buffer);

#endif //UI_MYSTREAMPARSER_H
