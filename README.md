# Qt串口通信系统（上位机 + STM32下位机）

## 项目简介
这是一个基于Qt和STM32的串口通信系统，实现了PC与STM32单片机之间的实时数据交互。系统采用模块化设计，包含上位机界面程序和下位机控制程序。

## 系统架构
### 上位机（Qt程序）
- 基于Qt 5.x开发的串口通信界面
- 采用面向对象的设计方法
- 实现串口数据的实时收发和显示
- 支持串口参数动态配置
- 提供友好的图形化操作界面

### 下位机（STM32程序）
- 基于STM32H750VBT6单片机（ARM Cortex-M7内核）
- 使用STM32 HAL库开发
- 基于wouoUI的OLED显示功能
- 串口DMA收发 + 空闲中断 + 环形缓冲区
- Multi Button按键控制
- GPIO控制功能
- 数据流解析器

## 功能特点
### 上位机功能
- 串口参数配置（波特率、数据位、停止位、校验位）
- 串口数据发送和接收显示
- 实时数据波形显示
- 数据解析和处理
- 错误检测和提示

### 下位机功能
- 串口DMA发送和接收（空闲中断）
- 环形缓冲区数据管理
- OLED显示（基于wouoUI）
- 多按键控制（Multi Button）
- GPIO控制
- 数据流解析器

## 开发环境
### 上位机环境
- Qt 5.15.2
- Qt Creator 4.12.2
- MinGW 64-bit
- Windows 10/11

### 下位机环境
- CLion 2023.x
- STM32CubeMX 6.8.0
- STM32 HAL库
- OpenOCD
- ARM GCC工具链
- CMake 3.x

## 项目结构 
```
Qt_Serial_Port_ui/
├── Serial_port_ui/          # Qt上位机项目
│   ├── src/                # 源代码
│   │   ├── main.cpp       # 程序入口
│   │   ├── mainwindow.cpp # 主窗口实现
│   │   └── serial.cpp     # 串口类实现
│   ├── include/           # 头文件
│   │   ├── mainwindow.h   # 主窗口声明
│   │   └── serial.h       # 串口类声明
│   └── ui/                # 界面文件
│       └── mainwindow.ui  # 主窗口界面
├── STM32_Code/            # STM32下位机程序
│   ├── Core/              # 核心代码
│   │   ├── Src/          # 源文件
│   │   │   ├── main.c    # 主程序
│   │   │   ├── gpio.c    # GPIO配置
│   │   │   ├── usart.c   # 串口配置
│   │   │   ├── button.c  # 按键处理
│   │   │   └── oled.c    # OLED显示
│   │   └── Inc/          # 头文件
│   ├── Drivers/          # HAL驱动
│   ├── .idea/            # CLion配置
│   ├── cmake/            # CMake配置
│   ├── CMakeLists.txt    # CMake主配置
│   └── STM32F103C8Tx_FLASH.ld # 链接脚本
└── Doc/                   # 文档
```

## 编译与运行
### 上位机编译
1. 安装Qt 5.15.2及以上版本
2. 使用Qt Creator打开`Serial_port_ui.pro`
3. 配置编译环境（MinGW 64-bit）
4. 编译运行项目

### 下位机编译
1. 环境准备：
   - 安装CLion
   - 安装ARM GCC工具链
   - 安装OpenOCD
   - 安装STM32CubeMX

2. 使用STM32CubeMX生成代码：
   - 配置芯片型号为STM32H750VBT6
   - 配置时钟树（最高可达480MHz）
   - 配置外设（USART、GPIO等）
   - 生成代码，选择Toolchain/IDE为"Other Toolchains (GPDSC)"

3. CLion配置：
   - 打开项目
   - 配置工具链（File -> Settings -> Build,Execution,Deployment -> Toolchains）
   - 配置CMake（File -> Settings -> Build,Execution,Deployment -> CMake）

4. 编译和下载：
   - 使用CLion编译项目
   - 通过OpenOCD下载程序到STM32

## 硬件连接
1. STM32引脚定义：
   - PA9 (UART1_TX)
   - PA10 (UART1_RX)
   - PB6-PB7 (I2C1: OLED)
   - PA0-PA3 (按键输入)
   - PC13 (LED指示)

2. 连接方式：
   - USB转TTL模块 <-> STM32 UART
   - OLED显示屏 <-> I2C接口
   - 按键模块 <-> GPIO
   - 5V供电

## 通信协议
### 数据流解析器说明
数据流解析器是一个通用的数据解析工具，支持自定义格式的数据解析。

解析器配置参数：
```c
/**
 * @param headStr  数据帧头字符串
 * @param tailStr  数据帧尾字符串
 * @param divStr   数据分隔符
 * @param typeList 数据类型列表
 */
```

数据类型支持：
- " " : 忽略该字段
- "s" : 字符串类型
- "f" : 浮点数类型
- "d" : 整数类型

示例：
```c
// 解析器初始化
stream_parser_init(&parser, "$", "*", ",", "f");

// 数据帧格式
$数据1,数据2,数据3*

// 实际数据示例
$123.45,67.89,0.123*
```

### 串口配置
- 波特率：115200
- 数据位：8
- 停止位：1
- 校验位：无
- 流控制：无

## 使用说明
1. 连接硬件
2. 运行上位机程序
3. 选择正确的串口号（一般为COMx）
4. 配置串口参数
5. 点击"打开串口"
6. 观察数据显示

## 项目状态
- [x] 串口通信基础功能
- [x] 数据流解析功能
- [x] OLED显示功能
- [x] 按键控制功能
- [ ] 数据记录功能
- [ ] 参数配置功能
- [ ] 自动重连功能

## 作者
- [jump0knight](https://github.com/jump0knight) - Qt上位机开发
- [Z1R343L-D77](https://github.com/Z1R343L-D77) - STM32下位机开发

## 许可证
本项目采用 [GPL-3.0](LICENSE) 许可证
