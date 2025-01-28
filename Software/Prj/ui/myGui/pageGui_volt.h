/**
  ******************************************************************************
  * @file           : pageGui_volt.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/28
  ******************************************************************************
  */

#ifndef UI_PAGEGUI_VOLT_H
#define UI_PAGEGUI_VOLT_H

#include "menu.h"

#define AMPS_RATIO		(1.0 / 0.05 / 50)

//电压测量页面变量
//开发板模拟引脚
//曲线相关
#define   WAVE_SAMPLE         1                          //采集倍数
#define   WAVE_W              94                          //波形宽度
#define   WAVE_L              24                          //波形左边距
#define   WAVE_U              0                           //波形上边距
#define   WAVE_MAX            27                          //最大值
#define   WAVE_MIN            3                           //最小值
#define   WAVE_BOX_H          32                          //波形边框高度
#define   WAVE_BOX_W          94                          //波形边框宽度
#define   WAVE_BOX_L_S        24                          //波形边框左边距
//列表和文字背景框相关
#define   VOLT_FONT           u8g2_font_helvB18_tr        //电压数字字体
#define   VOLT_TEXT_BG_L_S    24                          //文字背景框左边距
#define   VOLT_TEXT_BG_W      94                          //文字背景框宽度
#define   VOLT_TEXT_BG_H      29                          //文字背景框高度

typedef struct{
    uint8_t wave_index;

    int     ch0_adc[WAVE_SAMPLE * WAVE_W];
    int     ch0_wave[WAVE_W];

    float   val;
    float   text_bg_r;
    float   text_bg_r_trg;
} _volt;
extern _volt volt;

extern M_SELECT volt_menu[4];

void volt_param_init(void);
void volt_show(void);
void volt_proc(void);

#endif //UI_PAGEGUI_VOLT_H
