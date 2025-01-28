/**
  ******************************************************************************
  * @file           : pageGui_volt.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/28
  ******************************************************************************
  */
#include "pageGui_volt.h"
extern u8g2_t u8g2;
_volt volt;

M_SELECT volt_menu[4] =
        {
                {"EV"},
                {"EA"},
                {"A1"},
                {"A2"},
        };

// 电压测量页初始化
void volt_param_init(void){
    volt.text_bg_r = 0;
    volt.text_bg_r_trg = VOLT_TEXT_BG_W;
    memset(volt.ch0_wave,'\0', sizeof(volt.ch0_wave));
    memset(volt.ch0_adc,'\0', sizeof(volt.ch0_adc));
}

// 电压页面显示函数
void volt_show(void){
    // 使用列表类显示选项
    list_show(volt_menu, M_VOLT);
    // 计算动画过渡值
    animation(&volt.text_bg_r, &volt.text_bg_r_trg, TAG_ANI);
    // 设置曲线颜色，0透显，1实显，2反色，这里用实显
    u8g2_SetDrawColor(&u8g2, 1);
    // 绘制电压曲线和外框
    volt.val = 0;
    u8g2_DrawFrame(&u8g2, WAVE_BOX_L_S, 0, WAVE_BOX_W, WAVE_BOX_H);
    u8g2_DrawFrame(&u8g2, WAVE_BOX_L_S + 1, 1, WAVE_BOX_W - 2, WAVE_BOX_H - 2);

    if (list.box_y == list.box_y_trg[ui.layer] && list.y == list.y_trg){
        if(ui.select[ui.layer] == 0){
            memcpy(volt.ch0_adc, volt.ch0_adc + 1, WAVE_W-2);
            for (int i = 1; i < WAVE_W - 1; i++){
                volt.val += power_monitor_read_value(ui.select[ui.layer]);
                volt.ch0_adc[i] =  power_monitor_read_value(ui.select[ui.layer]);

                volt.ch0_wave[i] = map_number((volt.ch0_adc[i - 1]), 0, 4096, WAVE_MAX, WAVE_MIN);
                u8g2_DrawLine(&u8g2, WAVE_L + i - 1, WAVE_U + volt.ch0_wave[i - 1], WAVE_L + i, WAVE_U + volt.ch0_wave[i]);
            }
        }else if(ui.select[ui.layer] == 2){
            for (int i = 1; i < WAVE_W - 1; i++){
                volt.val += sine_wave[volt.wave_index - 1] * 100; // 填充新数据
                volt.ch0_wave[i] = map_number(sine_wave[i - 1] * 100, 0, 330, WAVE_MAX, WAVE_MIN);
                u8g2_SetDrawColor(&u8g2, 1);
                u8g2_DrawLine(&u8g2, WAVE_L + i - 1, WAVE_U + volt.ch0_wave[i - 1], WAVE_L + i, WAVE_U + volt.ch0_wave[i]);
            }
            // 清除画面
            if(volt.ch0_wave[WAVE_W-2] != WAVE_MAX){
                // 清楚区域内画的图像
                u8g2_SetDrawColor(&u8g2, 0);
                for (int i = 1; i < WAVE_W - 1; i++){
                    volt.ch0_wave[i] = map_number(sine_wave[i - 1] * 100, 0, 330, WAVE_MAX, WAVE_MIN);
                    u8g2_DrawLine(&u8g2, WAVE_L + i - 1, WAVE_U + volt.ch0_wave[i - 1], WAVE_L + i, WAVE_U + volt.ch0_wave[i]);
                }
                // 重置缓存
                memset(sine_wave, 0, sizeof(sine_wave));
                volt.ch0_wave[WAVE_W-2] = WAVE_MAX;
                u8g2_SetDrawColor(&u8g2, 1);
            }

        }

    }
    // 绘制电压值
    u8g2_SetFontDirection(&u8g2, 0);
    u8g2_SetFont(&u8g2, VOLT_FONT);
    if(ui.select[ui.layer] == 0){
        volt.val = volt.val / WAVE_W;
        volt.val = (volt.val / 4096.0 * 3.3);
        u8g2_DrawStr(&u8g2, 39, DISP_H - 6, ftoa(volt.val));
        u8g2_DrawStr(&u8g2, DISP_W-28, DISP_H - 6, "V");
    }
    else if((ui.select[ui.layer] == 1)){
        volt.val = volt.val / WAVE_W;
        volt.val = ((volt.val / 4096.0 * 3.3)-1.1)/(AMPS_RATIO);
        u8g2_DrawStr(&u8g2, 39, DISP_H - 6, ftoa(volt.val));
        u8g2_DrawStr(&u8g2, DISP_W-28, DISP_H - 6, "A");
    }
    else if((ui.select[ui.layer] == 2)){
        volt.val = volt.val / WAVE_W;
        volt.val = (volt.val / 100.0);
        u8g2_DrawStr(&u8g2, 39, DISP_H - 6, ftoa(volt.val));
        u8g2_DrawStr(&u8g2, DISP_W-28, DISP_H - 6, "V");
    }
    // 绘制列表选择框和电压文字背景
    u8g2_SetDrawColor(&u8g2, 2);
    u8g2_DrawBox(&u8g2, VOLT_TEXT_BG_L_S, DISP_H - VOLT_TEXT_BG_H, volt.text_bg_r, VOLT_TEXT_BG_H);
    // 反转屏幕内元素颜色，白天模式遮罩
    if (!ui.param[DARK_MODE])
        u8g2_DrawBox(&u8g2, 0, 0, DISP_W, DISP_H);
}

// 电压测量页处理函数
void volt_proc(void){
    volt_show();
    if (btn.pressed){
        btn.pressed = false;
        switch (btn.id){
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                switch(ui.select[ui.layer]){
                    case 2:
                        volt.wave_index = 0;
                        break;
                }
                break;
            case BTN_ID_SP:
            case BTN_ID_LP:
                ui.index = M_MAIN;
                ui.state = S_LAYER_OUT;
                break;
        }
    }
}