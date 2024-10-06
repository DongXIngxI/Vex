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
  char buffer[12]; // �㹻�洢һ��32λ�������ַ�����ʾ���������źͽ�������
    int i = 0;

    // ������
    if (data < 0) {
        uart_write(reg, '-'); // ���͸���
        data = -data; // תΪ����
    }
    // ������ת��Ϊ�ַ���������洢
    if (data == 0) {
        buffer[i++] = '0'; // �������� 0
    } else {
        while (data> 0) {
            buffer[i++] = (data % 10) + '0'; // ��ȡ���һλ���ֲ�ת��Ϊ�ַ�
          data /= 10; // ȥ�����һλ
        }
    }
    // �����ַ�������ת�ַ�˳��
    for (int j = i - 1; j >= 0; j--) {
        uart_write(reg, buffer[j]); // ��������ַ�
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
