/**
  ******************************************************************************
  * @file           : pageGui_serial.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/25
  ******************************************************************************
  */

#ifndef UI_PAGEGUI_SERIAL_H
#define UI_PAGEGUI_SERIAL_H

#include "menu.h"

enum{
    BT_115200 = 0,
    BT_9600,
    BT_460800,
};
typedef struct{
    float y;
    float y_trg;
    uint8_t data_index;
    uint8_t sw[5];
    uint8_t bund;
    uint8_t bund_index;
} show_serial;
extern show_serial show_serial_data;
extern M_SELECT serial_menu[7];

void serial_show_proc(void);
void serial_proc(void);

void serial_show_init(void);
void serial_pram_init(void);

void PrintVarFormat(const char *format,...);

#endif //UI_PAGEGUI_SERIAL_H
