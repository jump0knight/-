/**
  ******************************************************************************
  * @file           : bsp_key.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/20
  ******************************************************************************
  */

#ifndef INC_002_G_BSP_KEY_H
#define INC_002_G_BSP_KEY_H

#include "bsp_system.h"

enum {
    GPIO_LOW_LEVEL = 0,
    GPIO_HIGH_LEVEL
};

void myButton_init(void);


#endif //INC_002_G_BSP_KEY_H
