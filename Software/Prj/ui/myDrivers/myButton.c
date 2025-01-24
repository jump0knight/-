/**
  ******************************************************************************
  * @file           : myButton.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/20
  ******************************************************************************
  */
#include "myButton.h"

#define EVENT_CB(ev)   if(handle->cb[ev])handle->cb[ev]((void*)handle)
#define PRESS_REPEAT_MAX_NUM  15  /*!< 按键重复次数的最大值 */

// 按钮句柄链表头指针
static struct Button* head_handle = NULL;

static void button_handler(struct Button* handle);

/**
  * @brief  初始化按钮句柄结构体。
  * @param  handle: 按钮句柄结构体指针。
  * @param  pin_level: 读取连接按钮的HAL GPIO电平的函数指针。
  * @param  active_level: 按键按下时的GPIO电平。
  * @param  button_id: 按钮ID。
  * @retval None
  */
void button_init(struct Button* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id)
{
    memset(handle, 0, sizeof(struct Button));
    handle->event = (uint8_t)NONE_PRESS;
    handle->hal_button_Level = pin_level;
    handle->button_level = !active_level;
    handle->active_level = active_level;
    handle->button_id = button_id;
}

/**
  * @brief  绑定按钮事件回调函数。
  * @param  handle: 按钮句柄结构体指针。
  * @param  event: 触发事件类型。
  * @param  cb: 回调函数指针。
  * @retval None
  */
void button_attach(struct Button* handle, PressEvent event, BtnCallback cb)
{
    handle->cb[event] = cb;
}

/**
  * @brief  查询发生的按钮事件。
  * @param  handle: 按钮句柄结构体指针。
  * @retval 返回按钮事件类型。
  */
PressEvent get_button_event(struct Button* handle)
{
    return (PressEvent)(handle->event);
}

/**
  * @brief  按钮驱动核心函数，负责状态机的运行。
  * @param  handle: 按钮句柄结构体指针。
  * @retval None
  */
static void button_handler(struct Button* handle)
{
    uint8_t read_gpio_level = handle->hal_button_Level(handle->button_id);

    // 增加计数器工作时间
    if((handle->state) > 0) handle->ticks++;

    /*------------button debounce handle 消抖---------------*/
    if(read_gpio_level != handle->button_level) { //not equal to prev one
        //continue read 3 times same new level change
        if(++(handle->debounce_cnt) >= DEBOUNCE_TICKS) {
            handle->button_level = read_gpio_level;
            handle->debounce_cnt = 0;
        }
    } else { //level not change ,counter reset.
        handle->debounce_cnt = 0;
    }

    /*-----------------State machine 状态机-------------------*/
    switch (handle->state){
        case 0:
            if(handle->button_level == handle->active_level) {	// 按键按下
                handle->event = (uint8_t)PRESS_DOWN;
                EVENT_CB(PRESS_DOWN);
                handle->ticks = 0;
                handle->repeat = 1;
                handle->state = 1;
            } else {
                handle->event = (uint8_t)NONE_PRESS;
            }
            break;

        case 1:
            if(handle->button_level != handle->active_level) { // 按键释放
                handle->event = (uint8_t)PRESS_UP;
                EVENT_CB(PRESS_UP);
                handle->ticks = 0;
                handle->state = 2;
            } else if(handle->ticks > LONG_TICKS) {
                handle->event = (uint8_t)LONG_PRESS_START;
                EVENT_CB(LONG_PRESS_START);
                handle->state = 5;
            }
            break;

        case 2:
            if(handle->button_level == handle->active_level) { // 再次按下
                handle->event = (uint8_t)PRESS_DOWN;
                EVENT_CB(PRESS_DOWN);
                if(handle->repeat != PRESS_REPEAT_MAX_NUM) {
                    handle->repeat++;
                }
                EVENT_CB(PRESS_REPEAT); // 重复触发
                handle->ticks = 0;
                handle->state = 3;
            } else if(handle->ticks > SHORT_TICKS) { // 超时释放
                if(handle->repeat == 1) {
                    handle->event = (uint8_t)SINGLE_CLICK;
                    EVENT_CB(SINGLE_CLICK);
                } else if(handle->repeat == 2) {
                    handle->event = (uint8_t)DOUBLE_CLICK;
                    EVENT_CB(DOUBLE_CLICK); // 重复触发
                }
                handle->state = 0;
            }
            break;

        case 3:
            if(handle->button_level != handle->active_level) { // 按键释放
                handle->event = (uint8_t)PRESS_UP;
                EVENT_CB(PRESS_UP);
                if(handle->ticks < SHORT_TICKS) {
                    handle->ticks = 0;
                    handle->state = 2; // 重复按压
                } else {
                    handle->state = 0;
                }
            } else if(handle->ticks > SHORT_TICKS) { // 按下保持时间在SHORT_TICKS和LONG_TICKS之间
                handle->state = 1;
            }
            break;

        case 5:
            if(handle->button_level == handle->active_level) {
                handle->event = (uint8_t)LONG_PRESS_HOLD;// 持续长按触发
                EVENT_CB(LONG_PRESS_HOLD);
            } else {
                handle->event = (uint8_t)PRESS_UP;// 按键释放
                EVENT_CB(PRESS_UP);
                handle->state = 0;// 重置状态
            }
            break;
        default:
            handle->state = 0;// 重置状态
            break;
    }
}

/**
  * @brief  启动按钮工作，将句柄加入工作列表。
  * @param  handle: 目标句柄结构体指针。
  * @retval 0: 成功。 -1: 句柄已存在。
  */
int button_start(struct Button* handle)
{
    struct Button* target = head_handle;
    while(target) {
        if(target == handle) return -1;	// 已经存在
        target = target->next;
    }
    handle->next = head_handle;
    head_handle = handle;
    return 0;
}

/**
  * @brief  停止按钮工作，从工作列表中移除句柄。
  * @param  handle: 目标句柄结构体指针。
  * @retval None
  */
void button_stop(struct Button* handle)
{
    struct Button** curr;
    for(curr = &head_handle; *curr; ) {
        struct Button* entry = *curr;
        if(entry == handle) {
            *curr = entry->next;
//			free(entry);
            return;//glacier add 2021-8-18
        } else {
            curr = &entry->next;
        }
    }
}

/**
  * @brief  背景定时器，每5ms调用一次。
  * @param  None.
  * @retval None
  */
void button_ticks(void)
{
    struct Button* target;
    for(target=head_handle; target; target=target->next) {
        button_handler(target);
    }
}

