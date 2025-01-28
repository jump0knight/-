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

sParser_t parser;
char buffList[4][STRING_BUFFER_SIZE];

// 初始化一个包含20个元素的元数据数组，用于存储特定数据缓冲区
metaData_t databuff[20] = {
        [0] = {buffList[0]},
        [3] = {buffList[1]},
        [5] = {buffList[2]},
        [10] = {buffList[3]}
};

// 定义格式化字符串，用于数据输出
char *fmtStr = "ffdd";

#if USE_STRING_PARSE
#include "stdlib.h"
#endif

#define IS_NUMBER(ch) (ch >= '0' && ch <= '9')

static char* errorMsg[] = {
        "Error: malloc Failed.",
        "Error: String parser disabled.",
        "Error: Type list error."
};

/**
 * 初始化解析器对象
 *
 * @param parser 解析器对象指针
 * @param headStr 标记字符串的起始标识，用于标识解析的起始位置
 * @param tailStr 标记字符串的结束标识，用于标识解析的结束位置
 * @param divStr 分隔符字符串，用于分隔不同的数据项
 * @param typeList 类型列表字符串，用于指示数据项的类型
 *
 * @note 本函数初始化解析器对象的各种成员变量，为解析过程做准备。
 *       对于空指针传入的字符串，相应长度被设置为0。
 */
void SParser_Init(pSParser_t parser, char* headStr, char* tailStr, char* divStr, char* typeList){
    parser->headStr = headStr;
    parser->headStrLen = headStr == NULL ? 0 : strlen(headStr);
    parser->tailStr = tailStr;
    parser->TailStrLen = tailStr == NULL ? 0 : strlen(tailStr);
    parser->divStr = divStr;
    parser->divStrLen = divStr == NULL ? 0 : strlen(divStr);
    parser->typeList = typeList;
    parser->chPtr[0] = headStr;
    parser->typePtr = parser->typeList;
    parser->buff[0] = parser->buff[1] = parser->buff[2] = parser->buff[3] = 0;
    parser->mState = FindHead;
}

static metaData_t Parse_Intenger(pSParser_t parser, const char ch){
    metaData_t temp = { 0 };
    if (parser->buff[0] == 0 && ch == '-') {
        parser->buff[0] = -1;
    } else if (IS_NUMBER(ch)) {
        parser->buff[2] = parser->buff[2] * 10 + ch - '0';
    } else if (ch == *parser->tailStr || ch == *parser->divStr || ch == '.') {
        temp.intenger = parser->buff[0] == 0 ? parser->buff[2] : parser->buff[2] * -1;
        parser->buff[0] = parser->buff[2] = 0;
        return temp;
    }
    return temp;
}


static metaData_t Parse_Float(pSParser_t parser, const char ch){
    metaData_t temp = { 0 };
    if ((temp = Parse_Intenger(parser, ch)).intenger) {
        parser->buff[1 + parser->buff[3]] = temp.intenger;
    }
    if (ch == '.') {
        parser->buff[3] = 1;
    }
    if (ch == *parser->tailStr || ch == *parser->divStr) {
        temp.flt = parser->buff[2];
        while (temp.flt >= 1) {
            temp.flt /= 10;
        }
        temp.flt = (floatTypdef)parser->buff[1] + (parser->buff[1] >= 0 ? temp.flt : -temp.flt);
        memset(parser->buff, 0, 4 * sizeof(size_t));
        return temp;
    }
    return temp;
}

#if USE_STRING_PARSE
static char* Parse_String(pSParser_t parser, char* strBuff, const char ch)
{
    if (parser->buff[3] == 0) {
        if (strBuff == NULL) {
            strBuff = malloc(STRING_BUFFER_SIZE * sizeof(char));

            if (NULL == strBuff) {
                return errorMsg[0];
            }
        }

        parser->buff[3] = 1;
        parser->buff[0] = parser->buff[1] = (size_t)strBuff;
    }

    if (ch == *parser->tailStr || ch == *parser->divStr) {
        char* temp = (char*)parser->buff[1];

        *(char*)parser->buff[0] = '\0';
        parser->buff[0] = parser->buff[3] = parser->buff[1] = 0;
        return temp;
    }

    if (parser->buff[0] == 0 || ((char*)parser->buff[0] - (char*)parser->buff[1]) >= STRING_BUFFER_SIZE)
        return NULL;

    *(char*)parser->buff[0] = ch;
    parser->buff[0] += sizeof(char);

    return NULL;
}
#endif

/**
 * 比较字符串与字符是否相等。
 *
 * 该函数用于比较解析器对象中的字符串与给定字符。如果比较成功，则返回1；否则返回0。
 * 比较从指定位置开始，直到字符串结束或发现不匹配为止。
 *
 * @param parser 解析器对象指针，包含要比较的字符串。
 * @param str 要比较的字符串指针。
 * @param strLen 字符串长度。
 * @param ch 要比较的字符。
 * @param pSelect 指示解析器对象中要比较的字符串索引。
 *
 * @return 返回值说明：
 * 1: 比较相等
 * 0: 比较不相等
 */
static int CompareString(pSParser_t parser, const char* str, const int strLen, const char ch, const int pSelect){
    // 如果解析器对象中指定位置的指针为NULL，直接返回相等
    if (parser->chPtr[pSelect] == NULL) {
        return 1;
    }
    // 如果当前字符相等，进入EqualHook标签进行后续处理
    else if (ch == *parser->chPtr[pSelect]) {
        EqualHook:
        // 如果字符串长度为1，直接返回相等
        if (strLen == 1) {
            return 1;
        } else {
            // 移动指针到下一个字符，并检查是否到达字符串末尾
            parser->chPtr[pSelect] = parser->chPtr[pSelect] + 1;
            if (*parser->chPtr[pSelect] == '\0')
                return 1;
        }
    } else {
        // 如果字符不相等，重置指针并重新检查
        parser->chPtr[pSelect] = (char*)str;
        if (ch == *parser->chPtr[pSelect]) {
            goto EqualHook;
        }
    }

    // 如果所有检查均未通过，返回不相等
    return 0;
}


/**
 * @brief 解析数据流中的元数据
 *
 * 本函数根据解析器的状态机设计，通过不断读取字符来解析数据
 * 它支持解析整数（'d'）、浮点数（'f'）和字符串（'s'）类型的数据
 * 当解析到有效数据时，将其存储在dataArray中
 *
 * @param parser 解析器对象指针，包含解析所需的信息和状态
 * @param dataArray 元数据数组指针，用于存储解析后的数据
 * @param ch 当前读取的字符，用于解析
 * @return int 返回1表示成功解析一段数据，返回0表示解析失败或正在进行中
 */
int SParser_Parse(pSParser_t parser, pMetaData_t dataArray, const char ch){
    // 根据当前解析状态执行相应的逻辑
    switch (parser->mState) {
        // 寻找数据头状态
        case FindHead:
            // 如果当前字符与数据头匹配，则准备开始解析
            if (CompareString(parser, parser->headStr, parser->headStrLen, ch, 0)) {
                parser->chPtr[0] = parser->divStr;
                parser->chPtr[1] = parser->tailStr;
                parser->mState = Parse;
            }
            break;
        // 解析状态
        case Parse:
            // 根据数据类型解析当前字符
            switch (*parser->typePtr) {
                metaData_t temp;
                // 忽略空格和字符串结束符
                case ' ':
                case '\0':
                    break;
                // 解析整数类型数据
                case 'd':
                    if ((temp = Parse_Intenger(parser, ch)).intenger)
                        parser->temp = temp;
                    break;
                // 解析浮点数类型数据
                case 'f':
                    if ((temp = Parse_Float(parser, ch)).flt)
                        parser->temp = temp;
                    break;
                // 解析字符串类型数据
                case 's':
                    #if USE_STRING_PARSE
                        parser->temp.strPtr = Parse_String(parser, dataArray[parser->typePtr - parser->typeList].strPtr, ch);
                    #else
                        parser->temp.strPtr = errorMsg[1];
                    #endif
                    break;
                // 不支持的数据类型
                default:
                    parser->temp.strPtr = errorMsg[2];
                    break;
            }

            // 如果当前字符与数据分隔符匹配，则存储解析的数据，并准备解析下一种类型的数据
            if (CompareString(parser, parser->divStr, parser->divStrLen, ch, 0)) {
                parser->chPtr[0] = parser->divStr;

                if (*parser->typePtr != ' ' && *parser->typePtr != '\0') {
                    dataArray[parser->typePtr - parser->typeList] = parser->temp;
                }

                if (*(parser->typePtr) == '\0') {
                    goto EndOfParse;
                } else {
                    parser->typePtr++;
                }
            }

            // 如果当前字符与数据尾匹配，则存储解析的数据，并重置解析器状态
            if (CompareString(parser, parser->tailStr, parser->TailStrLen, ch, 1)) {
                if (*parser->typePtr != ' ')
                    dataArray[parser->typePtr - parser->typeList] = parser->temp;
                EndOfParse:
                parser->chPtr[0] = parser->headStr;
                parser->typePtr = parser->typeList;
                parser->mState = FindHead;
                return 1;//data yes
            }
        // 其他状态
        default:
            break;
    }
    return 0;//error
}




