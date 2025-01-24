/**
  ******************************************************************************
  * @file           : bsp_key.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/20
  ******************************************************************************
  */
#include "bsp_key.h"

enum Button_IDs {
    btn1_id=1,
    btn2_id,
    btn3_id,
    btn4_id,
};

struct Button btn1;
struct Button btn2;
struct Button btn3;
struct Button btn4;
/**
  * @brief  read_button_GPIO 按键读取函数
  * @note   None
  * @param  button_id 
  * @retval None
  */
uint8_t read_button_GPIO(uint8_t button_id)
{
    // you can share the GPIO read function with multiple Buttons
    switch(button_id)
    {
        case btn1_id:
            return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);
        case btn2_id:
            return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
        case btn3_id:
            return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);
        default:
            return 0;
    }
}
/**
  * @brief  button_callback 按键控制回调函数
  * @note   _btn->event 按键状态 _btn->buttun_id 按键编号
  * @param  void* btn 回调句柄
  * @retval None
  */
void button_callback(void* btn) {
    struct Button *_btn = btn;
    gui_btn_send_signal(_btn->button_id,_btn->event);
#if 0
    switch (_btn->event) {
        case PRESS_DOWN:
//			 LOG_INFO("---> key%d press down! <---\r\n",btn->button_id);
            switch (_btn->button_id) {
                case btn1_id:
                    led_setup(50, 0.5f, 1);
                    break;
                case btn2_id:
                    led_setup(50, 0.5f, 1);
                    break;
                default:
                    // 处理无效按键情况，例如记录日志或返回
                    break;
            }
            break;
        case PRESS_UP:
//			 LOG_INFO("---> key%d press up! <---\r\n",btn->button_id);
            break;
        case PRESS_REPEAT:
//			 LOG_INFO("---> key%d press repeat! <---\r\n",btn->button_id);
            break;
        case SINGLE_CLICK:
//			 LOG_INFO("---> key%d single click! <---\r\n",btn->button_id);
            break;
        case DOUBLE_CLICK:
//			 LOG_INFO("---> key%d double click! <***\r\n",btn->button_id);
            break;
        case LONG_PRESS_START:
//			 LOG_INFO("---> key%d long press start! <---\r\n",btn->button_id);
            break;
        case LONG_PRESS_HOLD:
//			 LOG_INFO("---> key%d long press hold! <***\r\n",btn->button_id);
            break;
    }
#endif
}

/**
  * @brief  mybutton_init 按键句柄初始化集合
  * @note   None
  * @param  None
  * @retval None
  */
void mybutton_init(void)
{
    button_init(&btn1, read_button_GPIO, 0, btn1_id);
    button_attach(&btn1, PRESS_DOWN,       button_callback);
    button_attach(&btn1, PRESS_UP,         button_callback);
//	button_attach(&btn1, PRESS_REPEAT,     button_callback);
//	button_attach(&btn1, SINGLE_CLICK,     button_callback);
//	button_attach(&btn1, DOUBLE_CLICK,     button_callback);
//	button_attach(&btn1, LONG_PRESS_START, button_callback);
    button_attach(&btn1, LONG_PRESS_HOLD, button_callback);
    button_start(&btn1);

    button_init(&btn2, read_button_GPIO, 0, btn3_id);
    button_attach(&btn2, PRESS_DOWN,       button_callback);
    button_attach(&btn2, PRESS_UP,         button_callback);
//	button_attach(&btn2, PRESS_REPEAT,     button_callback);
//	button_attach(&btn2, SINGLE_CLICK,     button_callback);
//	button_attach(&btn2, DOUBLE_CLICK,     button_callback);
    button_attach(&btn2, LONG_PRESS_START, button_callback);
    button_start(&btn2);

    button_init(&btn3, read_button_GPIO, 0, btn2_id);
    button_attach(&btn3, PRESS_DOWN,       button_callback);
    button_attach(&btn3, PRESS_UP,         button_callback);
//	button_attach(&btn2, PRESS_REPEAT,     button_callback);
//	button_attach(&btn2, SINGLE_CLICK,     button_callback);
//	button_attach(&btn2, DOUBLE_CLICK,     button_callback);
    button_attach(&btn3, LONG_PRESS_START, button_callback);
    button_start(&btn3);
//    //for example
//    button_attach(&btn2, PRESS_DOWN,       BTN2_PRESS_DOWN_Handler);
//    button_attach(&btn2, PRESS_UP,         BTN2_PRESS_UP_Handler);
//    button_attach(&btn2, PRESS_REPEAT,     BTN2_PRESS_REPEAT_Handler);
//    button_attach(&btn2, SINGLE_CLICK,     BTN2_SINGLE_Click_Handler);
//    button_attach(&btn2, DOUBLE_CLICK,     BTN2_DOUBLE_Click_Handler);
//    button_attach(&btn2, LONG_PRESS_START, BTN2_LONG_PRESS_START_Handler);
//    button_attach(&btn2, LONG_PRESS_HOLD,  BTN2_LONG_PRESS_HOLD_Handler);
}