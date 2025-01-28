/**
  ******************************************************************************
  * @file           : pagegGui_serial.c
  * @author         : 19816
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/25
  ******************************************************************************
  */
#include "pageGui_serial.h"

extern u8g2_t u8g2;
show_serial show_serial_data;
//添加界面第五部分 添加子界面显示列表，仿照其他函数显示
M_SELECT serial_menu[7] =
        {
                {"[ Serial ]"},
                {"- View "},
                {"+ Switch"},
                {"- Baud rate"},
                {"= 115200"},
                {"= 9600"},
                {"= 460800"},
        };


M_SELECT serial_data[6] =
        {
                {"001"},
                {"002"},
                {"003"},
                {"004"},
                {"005"},
                {"006"},
        };


void serial_pram_init(void){
    show_serial_data.data_index = 0;
    for(uint8_t i = 0; i < 6;i++){
        serial_data[i].m_select = " ";
    }
    check_box_m_init(show_serial_data.sw);
    check_box_s_init(&show_serial_data.bund, &show_serial_data.bund_index);
}

void serial_proc(void){
    list_show(serial_menu, M_SERIAL);
    if (btn.pressed){
        btn.pressed = false;
        switch (btn.id){
            case BTN_ID_CW:
            case BTN_ID_CC:
                    list_rotate_switch();//左右切换
                break;
            case BTN_ID_LP:
                ui.select[ui.layer] = 0;
            case BTN_ID_SP:
                switch (ui.select[ui.layer]){
                    case 0:// 返回更浅层级，长按被当作选择这一项，也是执行这一行
                        ui.index = M_MAIN;
                        ui.state = S_LAYER_OUT;
                        break;
                    case 1:
                        ui.index = M_SERIAL_SHOW;
                        ui.state = S_LAYER_IN;
                        break;
                    case 2:
                        check_box_m_select(ui.select[ui.layer] - 1);// enum 2 dot 取反位 是 ui.select[ui.layer]-1
                        if(!show_serial_data.sw[ui.select[ui.layer] - 1]){
                            HAL_UART_DMAStop(&huart1);// 停止当前的 DMA 接收
                            __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);// 禁用 DMA 半满中断
                        }else{
                            HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_dma_buffer, sizeof(uart_rx_dma_buffer));
                            __HAL_DMA_ENABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
                        }
                        break;
                    case 4:
                        check_box_s_select(BT_115200, ui.select[ui.layer]);
                        MX_USART1_UART_BUND_Init(115200);  // 设置波特率为 115200
                        break;
                    case 5:
                        check_box_s_select(BT_9600, ui.select[ui.layer]);
                        MX_USART1_UART_BUND_Init(9600);  // 设置波特率为 9600
                        break;
                    case 6:
                        check_box_s_select(BT_460800, ui.select[ui.layer]);
                        MX_USART1_UART_BUND_Init(460800);   // 设置波特率为 460800
                        break;
                }
        }
    }
}

void serial_show_init(void){
    show_serial_data.y = 20;
    show_serial_data.y_trg = 0;
}

void serial_show(void){
    animation(&show_serial_data.y, &show_serial_data.y_trg,WIN_ANI);//进入 滑动动画
    u8g2_SetDrawColor(&u8g2, 1);
    u8g2_SetFont(&u8g2,  u8g2_font_6x10_tr);

    for(uint8_t i = 0; i < 6;i++){
        u8g2_DrawStr(&u8g2, 4, (int16_t)show_serial_data.y +2 + (i + 1)*9, serial_data[i].m_select);
    }

    u8g2_DrawRFrame(&u8g2, 1, (int16_t)show_serial_data.y+1, DISP_W-2, DISP_H-2, 1);	// 绘制外框描边

    // 反转屏幕内元素颜色，白天模式遮罩
    u8g2_SetDrawColor(&u8g2, 2);
    if (!ui.param[DARK_MODE])
        u8g2_DrawBox(&u8g2, 0, 0, DISP_W, DISP_H);
}

void PrintVarFormat(const char *format,...)
{
    static char buff[128];
    int len;
    va_list args;
    va_start(args, format);
    len = vsnprintf(buff, sizeof(buff)+1, format, args);
    va_end(args);
    // 动态分配内存为 m_select 分配足够的空间
    serial_data[show_serial_data.data_index].m_select = (char *)malloc(len + 1);  // +1 是为了存储 null 终止符
    if (serial_data[show_serial_data.data_index].m_select != NULL) {
        // 复制 buff 中的字符串到 m_select
        strcpy(serial_data[show_serial_data.data_index].m_select, buff);
    }
    if(++show_serial_data.data_index > 5) show_serial_data.data_index = 0;
}
/**
 * serial_show_proc 显示view_log_printf
 *
 * 此函数用于处理串行显示过程，根据按钮按下的状态和ID执行相应的操作
 * 它主要通过检查按钮状态和ID来决定是否需要旋转列表、选择菜单项或切换显示状态
 */
void serial_show_proc(void){
    serial_show();//显示外框
    if (btn.pressed){
        btn.pressed = false;
        switch (btn.id){
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                break;
            case BTN_ID_LP:
                ui.select[ui.layer] = 0;
            case BTN_ID_SP: {
                switch (ui.select[ui.layer]){
                    case 0:// 如果选中的是第一个菜单项，设置UI状态为串行菜单显示
                        ui.index = M_SERIAL;
                        ui.state = S_LAYER_OUT;
                        break;
                }
            };break;
        }
    }
}

