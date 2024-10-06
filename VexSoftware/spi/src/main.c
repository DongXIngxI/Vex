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

    spi_init(SPI);
    uint32_t id[10]; // 存储 ID

    spi_select(SPI);
    SPI->DATA=0x0000009F;

    for (int i = 0; i < 3; i++) {
    SPI->DATA=0X01000000;
    while(!(SPI->DATA & (1 << 31))){
      id[i]= SPI->DATA ; 
      } 
    }
     spi_deselect(SPI); // 取消选择设备
 for(int i=0;i<10;i++) 
{
  print(UART,"JEDEC ID:", id[i]);
}
}

void irqCallback(){
  
}