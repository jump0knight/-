/**
  ******************************************************************************
  * @file           : myButton.h
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/20
  ******************************************************************************
  */

#ifndef INC_002_G_MYBUTTON_H
#define INC_002_G_MYBUTTON_H

#include <stdint.h>
#include <string.h>

//According to your need to modify the constants.
#define TICKS_INTERVAL    5	//ms
#define DEBOUNCE_TICKS    3	//MAX 7 (0 ~ 7)
#define SHORT_TICKS       (300 /TICKS_INTERVAL)
#define LONG_TICKS        (1000 /TICKS_INTERVAL)


typedef void (*BtnCallback)(void*);

typedef enum {
    PRESS_DOWN = 0,          // 按键按下事件
    PRESS_UP,                // 按键释放事件
    PRESS_REPEAT,            // 按键重复按下事件
    SINGLE_CLICK,            // 单击事件
    DOUBLE_CLICK,            // 双击事件
    LONG_PRESS_START,        // 长按开始事件
    LONG_PRESS_HOLD,         // 长按持续事件
    number_of_event,         // 事件数量，用于计数
    NONE_PRESS               // 无按键事件
}PressEvent;

typedef struct Button {
    uint16_t ticks;         // 记录按钮按下后的时间，用于控制重复事件的触发时机
    uint8_t  repeat : 4;    // 按钮重复事件的计数器，表示连续触发事件的次数
    uint8_t  event : 4;     // 当前按钮事件的类型，如按下、释放等
    uint8_t  state : 3;     // 按钮的当前状态，包括未按下、按下未释放等
    uint8_t  debounce_cnt : 3; // 去抖动计数器，用于消除按钮抖动
    uint8_t  active_level : 1; // 按钮的激活电平，0表示低电平激活，1表示高电平激活
    uint8_t  button_level : 1; // 当前按钮的电平状态
    uint8_t  button_id;     // 按钮的唯一标识符，用于区分不同的按钮
    uint8_t  (*hal_button_Level)(uint8_t button_id_); // 按钮硬件抽象层函数指针，用于获取按钮的物理状态
    BtnCallback  cb[number_of_event]; // 按钮事件回调函数数组，用于响应不同的按钮事件
    struct Button* next; // 指向下一个按钮结构体的指针，用于链表结构
}Button;

#ifdef __cplusplus
extern "C" {
#endif

void button_init(struct Button* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id);
void button_attach(struct Button* handle, PressEvent event, BtnCallback cb);
PressEvent get_button_event(struct Button* handle);
int  button_start(struct Button* handle);
void button_stop(struct Button* handle);
void button_ticks(void);

#ifdef __cplusplus
}
#endif



#endif //INC_002_G_MYBUTTON_H
