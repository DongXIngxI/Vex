/*
 * briey.h
 *
 *  Created on: Aug 24, 2016
 *      Author: clp
 */

#ifndef BRIEY_H_
#define BRIEY_H_

#include "timer.h"
#include "prescaler.h"
#include "interrupt.h"
#include "uart.h"
#include "gpio.h"
#include "spi.h"

#define CORE_HZ 50000000

#define GPIO_A_BASE    ((Gpio_Reg*)(0xF0000000))
#define GPIO_B_BASE    ((Gpio_Reg*)(0xF0001000))
#define UART           ((Uart_Reg*)(0xF0010000))
#define SPI              ((Spi_Reg*) (0xF0030000))


#define TIMER_PRESCALER ((Prescaler_Reg*)0xF0020000)
#define TIMER_INTERRUPT ((InterruptCtrl_Reg*)0xF0020010)
#define TIMER_A ((Timer_Reg*)0xF0020040)
#define TIMER_B ((Timer_Reg*)0xF0020050)
#define TIMER_C ((Timer_Reg*)0xF0020060)
#define TIMER_D ((Timer_Reg*)0xF0020070)

#define UART_SAMPLE_PER_BAUD 8

void print_string(Uart_Reg* reg, char *str)
{
    while (*str) {
        uart_write(reg, *str++);
    }
}
void print_number(Uart_Reg* reg, uint32_t data)
{
  char buffer[12]; // 足够存储一个32位整数的字符串表示（包括符号和结束符）
    int i = 0;

    // 处理负数
    if (data < 0) {
        uart_write(reg, '-'); // 发送负号
        data = -data; // 转为正数
    }
    // 将数字转换为字符串，反向存储
    if (data == 0) {
        buffer[i++] = '0'; // 处理数字 0
    } else {
        while (data> 0) {
            buffer[i++] = (data % 10) + '0'; // 获取最后一位数字并转换为字符
          data /= 10; // 去掉最后一位
        }
    }
    // 发送字符串（反转字符顺序）
    for (int j = i - 1; j >= 0; j--) {
        uart_write(reg, buffer[j]); // 逐个发送字符
    }
}
void print(Uart_Reg* reg, char *str, uint32_t data)
{
    print_string(reg, str);
    print_number(reg, data);
    uart_write(UART,'\n');
}
void delay(uint32_t ms)
{
    prescaler_init(TIMER_PRESCALER);
	timer_init(TIMER_A);
	TIMER_PRESCALER->LIMIT = 50000-1; //1 ms rate
	TIMER_A->LIMIT = ms-1;  //1 second rate
	TIMER_A->CLEARS_TICKS = 0x00010002;
    while (true)
    {
       while ((TIMER_A->VALUE) != TIMER_A->LIMIT)
       break;
    }
}

#endif /* BRIEY_H_ */
