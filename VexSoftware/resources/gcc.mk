# Set it to yes if you are using the sifive precompiled GCC pack
SIFIVE_GCC_PACK ?= yes
# sifive-gcc-pack 里面各种riscv的编译器都有，不用重新下载rv32im的编译器，下面的代码就是选择和配置编译器

ifeq ($(SIFIVE_GCC_PACK),yes)
	RISCV_NAME ?= riscv64-unknown-elf
	RISCV_PATH ?= /opt/riscv/
else
	RISCV_NAME ?= riscv32-unknown-elf
	ifeq ($(MULDIV),yes)
		RISCV_PATH ?= /opt/riscv32im/
	else
		RISCV_PATH ?= /opt/riscv32i/
	endif
endif
# 使用架构riscv32 指令集rv32im 原来文件是rv32i 因为要添加rv32m 所以我改成了rv32im
MABI=ilp32
MARCH := rv32im
ifeq ($(MULDIV),yes)
	MARCH := $(MARCH)m
endif
ifeq ($(COMPRESSED),yes)
	MARCH := $(MARCH)ac
endif
#CFLAGS 编译器配置 LDFLAGS 链接器配置，指定一些库选项和路径
CFLAGS += -march=$(MARCH)  -mabi=$(MABI)
LDFLAGS += -march=$(MARCH)  -mabi=$(MABI)