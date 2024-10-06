#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include <stdbool.h>

//0x00 -> 0x04 相差4个字节，32位，所以下面的寄存器结构体用32位，与地址对应
//0x00000000 表示32位 4个字节
typedef struct {
    volatile uint32_t DATA;
    volatile uint32_t STATUS;
    volatile uint32_t CONFIG;
    volatile uint32_t CLOCKDIVIDER;
    volatile uint32_t ssSetup;
    volatile uint32_t ssHold;
    volatile uint32_t ssDisable;
} Spi_Reg;

static void spi_init(Spi_Reg* reg)
{
    reg->CLOCKDIVIDER=1;
    reg->ssSetup=32;
    reg->ssHold=32;
    reg->ssDisable=32;
    reg->CONFIG=0x00; 
}
static void spi_select(Spi_Reg* reg)
{
    reg->DATA=0x11000000;
}
static void spi_deselect(Spi_Reg* reg)
{
    reg->DATA=0x10000000;
}
#endif