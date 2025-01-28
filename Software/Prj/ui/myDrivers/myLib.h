/**
  ******************************************************************************
  * @file           : myLib.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/26
  ******************************************************************************
  */

#ifndef UI_MYLIB_H
#define UI_MYLIB_H

#include "bsp_system.h"

float map_number(float num, float minInput, float maxInput, float minOutput, float maxOutput);

char *ditoa(uint32_t num);
char *ftoa(float num);

void SoftReset(void);

#endif //UI_MYLIB_H
