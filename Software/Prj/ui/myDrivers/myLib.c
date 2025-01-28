/**
  ******************************************************************************
  * @file           : bsp_system.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/26
  ******************************************************************************
  */
#include "myLib.h"

/**
 * 将一个数字从一个范围映射到另一个范围
 *
 * @param num 需要被映射的数字
 * @param minInput 输入范围的最小值     = 0.0;    	// 输入范围的最小值
 * @param maxInput 输入范围的最大值     = 4096.0; 	// 输入范围的最大值
 * @param minOutput 输出范围的最小值    = 0.0;   	// 输出范围的最小值
 * @param maxOutput 输出范围的最大值    = 32.0;  	// 输出范围的最大值
 * @return 映射后的数字
 *
 * 此函数不直接与特定的硬件或环境假设相关联，而是提供一个通用的数学映射功能
 * 它按比例将输入数字从其原始范围转换到目标范围，保持相对比例不变
 */
float map_number(float num, float minInput, float maxInput, float minOutput, float maxOutput){
    // 按比例映射
    float mappedNum = ((num - minInput) / (maxInput - minInput)) * (maxOutput - minOutput) + minOutput;
    return mappedNum;
}

//stdlib函数
char *ditoa(uint32_t num){
    static char str[10] = {0};
    memset(str, 0, sizeof(str));
    sprintf(str, "%d", num);
    return str;
}
char *ftoa(float num){
    static char str[10] = {0};
    memset(str, 0, sizeof(str));
    sprintf(str, "%.2f", num);
    return str;
}

//软件复位
void SoftReset(void){
    __set_FAULTMASK(1); // 关闭所有中断
    NVIC_SystemReset(); // 复位
}

//设置栈顶地址
//addr:栈顶地址
//__asm void MSR_MSP(uint32_t addr)
//{
////	MSR MSP, r0 			//set Main Stack value
////	BX r14
//}