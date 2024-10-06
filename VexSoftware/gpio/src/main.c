#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "vexcpu.h"

int main()
{  
	Uart_Config uartConfig;
	uartConfig.dataLength = 8;
	uartConfig.parity = NONE;
	uartConfig.stop = ONE;
	uartConfig.clockDivider = 50000000/8/115200-1;
	uart_applyConfig(UART,&uartConfig);
	print_string(UART,"rt\n");
   	GPIO_A_BASE->OUTPUT_ENABLE = 0x0000000F;

	while (true)
	{   
		delay(1000);
		GPIO_A_BASE->OUTPUT=0xFFFFFF0E;
		delay(1000);
		GPIO_A_BASE->OUTPUT=0xFFFFFF0D;
		delay(1000);
		GPIO_A_BASE->OUTPUT=0xFFFFFF0B;
		delay(1000);
		GPIO_A_BASE->OUTPUT=0xFFFFFF08;	
	}
}
// 中断还未成功，下面的中断函数没有用
void irqCallback()
{	uint32_t i;
	i=GPIO_A_BASE->OUTPUT+GPIO_B_BASE->INPUT;
	print_string(UART,"start\n");
	switch (i)
	{
	case 0x00000002:
	print_string(UART,"S1");
	break;
	case 0x00000003:
	if(GPIO_A_BASE->OUTPUT=0x00000001)
		print_string(UART,"S2");
	else 
		print_string(UART,"S5");
	break;
	case 0x00000005:
	if(GPIO_A_BASE->OUTPUT=0x00000001)
		print_string(UART,"S3");
	else 
		print_string(UART,"S9");
	break;
	case 0x00000009:
	if(GPIO_A_BASE->OUTPUT=0x00000001)
		print_string(UART,"S4");
	else 
		print_string(UART,"S13");
	break;
	case 0x00000004:
	print_string(UART,"S6");
	break;
	case 0x00000006:
	if(GPIO_A_BASE->OUTPUT=0x00000002)
		print_string(UART,"S7");
	else 
		print_string(UART,"S10");
	break;
	case 0x0000000B:
	print_string(UART,"S8");
	break;
	case 0x00000008:
	print_string(UART,"S11");
	break;
	case 0x0000000C:
	if(GPIO_A_BASE->OUTPUT=0x00000004)
		print_string(UART,"S12");
	else 
		print_string(UART,"S15");
	break;
	case 0x0000000A:
	print_string(UART,"S14");
	break;
	case 0x000000010:
	print_string(UART,"S16");
	break;
	default:break;
	}
	print_string(UART,"start\n");
}