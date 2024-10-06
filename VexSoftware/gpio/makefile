PROJ_NAME=gpio
DEBUG=yes
BENCH=no
MULDIV=no

# 查找文件
SRCS = 	$(wildcard src/*.c) \
	$(wildcard src/*.cpp)  \
	$(wildcard src/*.S)

# 找到链接脚本 链接脚本的作用是把生成的.o类型文件转换为可执行文件
LDSCRIPT = ../libs/linker.ld  
# 添加briey.h
INC += -I../../../libs/
# 添加外设头文件
INC += -I../libs/
# 执行对应目录下的makefile文件
include ../resources/gcc.mk
include ../resources/subproject.mk


			
