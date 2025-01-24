/**
  ******************************************************************************
  * @file           : myStreamParser.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/24
  ******************************************************************************
  */
#include "myStreamParser.h"

stream_parser_t parser;
// 初始化解析器
void stream_parser_init(stream_parser_t *parser, const char *headStr, const char *tailStr, const char *divStr, const char *typeList) {
    parser->headStr = headStr;
    parser->tailStr = tailStr;
    parser->divStr = divStr;
    parser->typeList = typeList;
    parser->state = 0;  // 初始状态
}
// 解析数据
// 解析数据函数：提取并打印浮动数
void parse_stream_data(stream_parser_t *parser, uint8_t *usart_read_buffer) {
    uint8_t temp[STRING_BUFFER_SIZE];  // 用于存储浮动数
    int i = 0;  // temp 数组的索引

    // 遍历读取缓冲区中的每个字符
    for (int j = 0; j < STRING_BUFFER_SIZE; j++) {
        uint8_t ch = usart_read_buffer[j];  // 获取当前字符

        // 如果字符是数字或小数点，继续构建浮动数
        if ((ch >= '0' && ch <= '9') || ch == '.') {
            temp[i++] = ch;  // 将字符添加到 temp 数组
        }
            // 如果遇到分隔符或尾标记，说明当前浮动数已经解析完成
        else if (ch == ',' || ch == *parser->tailStr || ch == '\0') {
            if (i > 0) {
                temp[i] = '\0';  // 结束当前浮动数的字符串
                float float_val = atof((char *)temp);  // 将字符串转换为浮动数
                MY_LOG(&huart1, "Parsed float: %.1f\n", float_val);  // 使用 MY_LOG 打印浮动数
                i = 0;  // 重置 temp 数组的索引
            }
            if (ch == *parser->tailStr) {
                break;  // 如果遇到尾标记，结束解析
            }
        }
    }
}

