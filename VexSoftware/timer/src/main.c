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

    print_string(UART,"hell");
	interruptCtrl_init(TIMER_INTERRUPT);
	prescaler_init(TIMER_PRESCALER);
	timer_init(TIMER_B);

	TIMER_PRESCALER->LIMIT = 50000-1; //1 ms rate

	TIMER_B->LIMIT = 1000-1;  //1 second rate
	TIMER_B->CLEARS_TICKS = 0x00010002;

	TIMER_INTERRUPT->PENDINGS = 0xF;
	TIMER_INTERRUPT->MASKS = 0x1;

    UART->STATUS = 2; //Enable RX interrupts
    UART->DATA='h';
    // for(;;)
    // {
    //         int* value =(int*) 0x8000000;
    //         *value =2;
    //         (*value)++;
    // }
}

void irqCallback(){
    if(TIMER_INTERRUPT->PENDINGS & 1){  
    //Timer A interrupt
        print(UART,"hello   ", 1);
        print_string(UART,"\n");
		TIMER_INTERRUPT->PENDINGS = 1;
	}
	while(UART->STATUS & (1 << 9)){ //UART RX interrupt
		UART->DATA = (UART->DATA) & 0xFF;
	}
	    

}
