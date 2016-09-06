################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal/src/stm32f7xx_hal.c \
../src/hal/src/stm32f7xx_hal_cortex.c \
../src/hal/src/stm32f7xx_hal_crc.c \
../src/hal/src/stm32f7xx_hal_crc_ex.c \
../src/hal/src/stm32f7xx_hal_dma.c \
../src/hal/src/stm32f7xx_hal_dma_ex.c \
../src/hal/src/stm32f7xx_hal_flash.c \
../src/hal/src/stm32f7xx_hal_flash_ex.c \
../src/hal/src/stm32f7xx_hal_gpio.c \
../src/hal/src/stm32f7xx_hal_i2c.c \
../src/hal/src/stm32f7xx_hal_i2c_ex.c \
../src/hal/src/stm32f7xx_hal_pwr.c \
../src/hal/src/stm32f7xx_hal_pwr_ex.c \
../src/hal/src/stm32f7xx_hal_rcc.c \
../src/hal/src/stm32f7xx_hal_rcc_ex.c \
../src/hal/src/stm32f7xx_hal_tim.c \
../src/hal/src/stm32f7xx_hal_tim_ex.c \
../src/hal/src/stm32f7xx_hal_uart.c 

OBJS += \
./src/hal/src/stm32f7xx_hal.o \
./src/hal/src/stm32f7xx_hal_cortex.o \
./src/hal/src/stm32f7xx_hal_crc.o \
./src/hal/src/stm32f7xx_hal_crc_ex.o \
./src/hal/src/stm32f7xx_hal_dma.o \
./src/hal/src/stm32f7xx_hal_dma_ex.o \
./src/hal/src/stm32f7xx_hal_flash.o \
./src/hal/src/stm32f7xx_hal_flash_ex.o \
./src/hal/src/stm32f7xx_hal_gpio.o \
./src/hal/src/stm32f7xx_hal_i2c.o \
./src/hal/src/stm32f7xx_hal_i2c_ex.o \
./src/hal/src/stm32f7xx_hal_pwr.o \
./src/hal/src/stm32f7xx_hal_pwr_ex.o \
./src/hal/src/stm32f7xx_hal_rcc.o \
./src/hal/src/stm32f7xx_hal_rcc_ex.o \
./src/hal/src/stm32f7xx_hal_tim.o \
./src/hal/src/stm32f7xx_hal_tim_ex.o \
./src/hal/src/stm32f7xx_hal_uart.o 

C_DEPS += \
./src/hal/src/stm32f7xx_hal.d \
./src/hal/src/stm32f7xx_hal_cortex.d \
./src/hal/src/stm32f7xx_hal_crc.d \
./src/hal/src/stm32f7xx_hal_crc_ex.d \
./src/hal/src/stm32f7xx_hal_dma.d \
./src/hal/src/stm32f7xx_hal_dma_ex.d \
./src/hal/src/stm32f7xx_hal_flash.d \
./src/hal/src/stm32f7xx_hal_flash_ex.d \
./src/hal/src/stm32f7xx_hal_gpio.d \
./src/hal/src/stm32f7xx_hal_i2c.d \
./src/hal/src/stm32f7xx_hal_i2c_ex.d \
./src/hal/src/stm32f7xx_hal_pwr.d \
./src/hal/src/stm32f7xx_hal_pwr_ex.d \
./src/hal/src/stm32f7xx_hal_rcc.d \
./src/hal/src/stm32f7xx_hal_rcc_ex.d \
./src/hal/src/stm32f7xx_hal_tim.d \
./src/hal/src/stm32f7xx_hal_tim_ex.d \
./src/hal/src/stm32f7xx_hal_uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/hal/src/%.o: ../src/hal/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -Wunused -Wuninitialized -Wall -Wextra -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wno-sign-compare -DSTM32F745xx -I../src/cmsis -I../src/cmsis_boot -I../src/kiss/inc -I../src/usart_lib -I../src/cmsis_lib/include_inline -I../src -I../src/hal/include -std=gnu11 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


