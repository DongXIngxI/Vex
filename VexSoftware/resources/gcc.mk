# Set it to yes if you are using the sifive precompiled GCC pack
SIFIVE_GCC_PACK ?= yes
# sifive-gcc-pack �������riscv�ı��������У�������������rv32im�ı�����������Ĵ������ѡ������ñ�����

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
# ʹ�üܹ�riscv32 ָ�rv32im ԭ���ļ���rv32i ��ΪҪ���rv32m �����Ҹĳ���rv32im
MABI=ilp32
MARCH := rv32im
ifeq ($(MULDIV),yes)
	MARCH := $(MARCH)m
endif
ifeq ($(COMPRESSED),yes)
	MARCH := $(MARCH)ac
endif
#CFLAGS ���������� LDFLAGS ���������ã�ָ��һЩ��ѡ���·��
CFLAGS += -march=$(MARCH)  -mabi=$(MABI)
LDFLAGS += -march=$(MARCH)  -mabi=$(MABI)