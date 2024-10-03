#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "vexcpu.h"

int main() {
	Uart_Config uartConfig;
	uartConfig.dataLength = 8;
	uartConfig.parity = NONE;
	uartConfig.stop = ONE;
	uartConfig.clockDivider = 50000000/8/115200-1;
	uart_applyConfig(UART,&uartConfig);

	uint32_t n1,n2;
	n1=8;
	n2=4;
	print(UART,"n1=",n1);
	print(UART,"n2=",n2);
	print(UART,"n1+n2=",n1+n2);
	print(UART,"n1-n2=",n1-n2);
	print(UART,"n1*n2=",n1*n2);
	print(UART,"n1/n2=",n1/n2);
	print(UART,"n1%n2=",n1%n2);
	// uart_write(UART,n1);
	// uart_write(UART,n2);
	// uart_write(UART,n1+n2);

    // print("Hello");
	// while(1){
	// 	for(uint32_t idx = '0';idx <= '9';idx++){
	// 		uart_write(UART, idx);
	// 	}
	// 	for(uint32_t idx = 'a';idx <= 'z';idx++){
	// 		uart_write(UART, idx);
	// 	}
		// for(uint32_t idx = 'A';idx <= 'Z';idx++){
		// 	uart_write(UART, idx);
		// }
	// }
}

void irqCallback(){

}
