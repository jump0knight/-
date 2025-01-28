/**
  ******************************************************************************
  * @file           : bsp_system.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/20
  ******************************************************************************
  */

#ifndef INC_002_G_BSP_SYSTEM_H
#define INC_002_G_BSP_SYSTEM_H

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stdarg.h"
#include "math.h"
#include "stm32h7xx_hal.h"
//Core

//myUser
#include "scheduler.h"
#include "bsp_key.h"
#include "bsp_uart.h"

//myDrivers
#include "myLib.h"
#include "myGpio.h"
#include "myButton.h"
#include "myTimeIR.h"
#include "myAdc.h"
#include "myRingBuffer.h"
#include "myStreamParser.h"

//myGui
#include "u8g2_oled.h"
#include "menu.h"


void loop(void);
void os_200hz_task(void);
void task_debug(void);
#endif //INC_002_G_BSP_SYSTEM_H
