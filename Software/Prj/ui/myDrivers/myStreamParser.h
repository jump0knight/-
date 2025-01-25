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

/**
 * @brief 配置是否使用 double 而不是 float 作为 "f" 类型。
 */
#define USE_DOUBLE (1)
#if USE_DOUBLE
typedef double floatTypdef;
#else
typedef float floatTypdef;
#endif

/**
 * @brief 配置是否使用字符串解析函数。
 * @note 字符串解析可能会通过 stdlib 中的 "malloc" 增加额外的内存使用。
 * @warning !!! 记得在使用完字符串内存后释放 !!!
 */
#define USE_STRING_PARSE (0)

/**
 * @brief 指定你提供的缓冲区大小。
 */
#define STRING_BUFFER_SIZE (64)

/**
 * @brief 定义用于返回值的元数据类型。
 */
typedef union MetaDataTypedef {
    void *strPtr;       // 定义一个指向字符串的指针变量
    floatTypdef flt;    // 定义一个浮点数变量flt,用于存储符合floatTypdef类型的数据
    int intenger;       // 定义一个整数变量intenger，用于存储整型数据
} metaData_t, *pMetaData_t;

/**
 * @brief 定义流解析器结构体。
 */
typedef struct StreamParser {
    char *headStr;      // 数据前的头字符串
    char *divStr;       // 数据间的分隔符字符串
    char *tailStr;      // 数据后的尾字符串
    /**
     * @note "typeList" 应该按照以下方式输入：
     * " " 表示忽略
     * "s" 表示字符串
     * "d" 表示整数
     * "f" 表示自定义浮点数
     */
    char *typeList;     // 数据类型列表
    char *typePtr;      // 当前类型指针

    char *chPtr[2];     // 字符指针数组

    /**
     * @brief 解析器缓冲区，结构如下：
     * | 符号 | 整数部分 | 小数部分 | 标志位 |
     */
    size_t buff[4];     // 缓冲区数组
    metaData_t temp;    // 临时元数据

    enum {
        FindHead = 0,       // 寻找头字符串状态
        Parse           // 解析状态
    } mState;           // 当前状态

    uint8_t headStrLen; // 头字符串长度
    uint8_t divStrLen;  // 分隔符字符串长度
    uint8_t TailStrLen; // 尾字符串长度
} sParser_t, *pSParser_t;

extern sParser_t parser;
extern char buffList[4][STRING_BUFFER_SIZE];
extern metaData_t databuff[20];
extern char *fmtStr;

/**
 * @brief 初始化解析器参数。
 *
 * @param parser 解析器句柄
 * @param headStr 数据前的头字符串
 * @param tailStr 数据后的尾字符串
 * @param divStr 数据间的分隔符字符串
 * @param typeList 头和尾之间的数据类型列表
 *
 * @note 对于 "headStr", "tailStr" 和 "divStr"：
 * 可以使用一个或多个字符作为参数字符串，但无论字符多少，它应该是一个 "字符串"。
 *
 * @note 对于 "typeList" 可以使用以下方式：
 * * " " 表示忽略；
 * * "s" 表示字符串；
 * * "f" 表示浮点数；
 * * "d" 表示整数。
 *
 * @example 假设你想解析以下 GPS NMEA 协议的数据：
 *      $GPGGA,092204.999,4250.5589,S,14718.5084,E,1,04,24.4,19.7,M,,,,0000*1F
 *      你可以使用 "$GP" 作为 headStr, "," 作为 divStr 和 "*" 作为 tailStr, 并使用
 *      " ffsfsddffs" 作为 typeList，我们将忽略 typeList 中未包含的所有数据。就像这样：
 *      SParser_Init(&parser, "$GP", "*", ",?", strList[0]);
 */
void SParser_Init(pSParser_t parser, char *headStr, char *tailStr, char *divStr, char *typeList);

/**
 * @brief 解析数据。
 *
 * @param parser 解析器句柄
 * @param dataArray 用于存储解析数据的元数据数组
 * @param ch 字节流中的每个字符
 * @return int 返回解析是否完成，具体如下：
 * * 0: 未完成；
 * * 1: 完成。
 *
 * @note    对于参数 "dataArray"：
 *          如果你设置了宏 USE_STRING_PARSE 为 1，这意味着你正在使用字符串解析函数，
 *          你应该确保 dataArray 中对应 "s" 在 typeList 中的元素在你的控制下。
 *          你应该这样设置：
 *              * NULL           : 如果你没有提供用于存储字符串的缓冲区；
 *              * BUFFER ADDRESS : 如果你可以提供用于存储字符串的缓冲区。
 *          另外，你的缓冲区最好大于或等于宏 STRING_BUFFER_SIZE，
 *          这是我们将为你的字符串创建的缓冲区大小，如果你给我们的是 NULL。
 */
int SParser_Parse(pSParser_t parser, pMetaData_t dataArray, const char ch);


#endif //UI_MYSTREAMPARSER_H
