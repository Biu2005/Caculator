################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/croutine.c \
../Core/Src/event_groups.c \
../Core/Src/heap_4.c \
../Core/Src/list.c \
../Core/Src/main.c \
../Core/Src/port.c \
../Core/Src/portasm.c \
../Core/Src/queue.c \
../Core/Src/stm32f0xx_hal_msp.c \
../Core/Src/stm32f0xx_hal_timebase_tim.c \
../Core/Src/stm32f0xx_it.c \
../Core/Src/stream_buffer.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f0xx.c \
../Core/Src/tasks.c \
../Core/Src/timers.c 

OBJS += \
./Core/Src/croutine.o \
./Core/Src/event_groups.o \
./Core/Src/heap_4.o \
./Core/Src/list.o \
./Core/Src/main.o \
./Core/Src/port.o \
./Core/Src/portasm.o \
./Core/Src/queue.o \
./Core/Src/stm32f0xx_hal_msp.o \
./Core/Src/stm32f0xx_hal_timebase_tim.o \
./Core/Src/stm32f0xx_it.o \
./Core/Src/stream_buffer.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f0xx.o \
./Core/Src/tasks.o \
./Core/Src/timers.o 

C_DEPS += \
./Core/Src/croutine.d \
./Core/Src/event_groups.d \
./Core/Src/heap_4.d \
./Core/Src/list.d \
./Core/Src/main.d \
./Core/Src/port.d \
./Core/Src/portasm.d \
./Core/Src/queue.d \
./Core/Src/stm32f0xx_hal_msp.d \
./Core/Src/stm32f0xx_hal_timebase_tim.d \
./Core/Src/stm32f0xx_it.d \
./Core/Src/stream_buffer.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f0xx.d \
./Core/Src/tasks.d \
./Core/Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Core/Inc -ID:/altium/FreeRTOSv202406.01-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/portable/MemMang -ID:/altium/FreeRTOSv202406.01-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/portable/GCC/ARM_CM0 -ID:/altium/FreeRTOSv202406.01-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/include -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/croutine.cyclo ./Core/Src/croutine.d ./Core/Src/croutine.o ./Core/Src/croutine.su ./Core/Src/event_groups.cyclo ./Core/Src/event_groups.d ./Core/Src/event_groups.o ./Core/Src/event_groups.su ./Core/Src/heap_4.cyclo ./Core/Src/heap_4.d ./Core/Src/heap_4.o ./Core/Src/heap_4.su ./Core/Src/list.cyclo ./Core/Src/list.d ./Core/Src/list.o ./Core/Src/list.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/port.cyclo ./Core/Src/port.d ./Core/Src/port.o ./Core/Src/port.su ./Core/Src/portasm.cyclo ./Core/Src/portasm.d ./Core/Src/portasm.o ./Core/Src/portasm.su ./Core/Src/queue.cyclo ./Core/Src/queue.d ./Core/Src/queue.o ./Core/Src/queue.su ./Core/Src/stm32f0xx_hal_msp.cyclo ./Core/Src/stm32f0xx_hal_msp.d ./Core/Src/stm32f0xx_hal_msp.o ./Core/Src/stm32f0xx_hal_msp.su ./Core/Src/stm32f0xx_hal_timebase_tim.cyclo ./Core/Src/stm32f0xx_hal_timebase_tim.d ./Core/Src/stm32f0xx_hal_timebase_tim.o ./Core/Src/stm32f0xx_hal_timebase_tim.su ./Core/Src/stm32f0xx_it.cyclo ./Core/Src/stm32f0xx_it.d ./Core/Src/stm32f0xx_it.o ./Core/Src/stm32f0xx_it.su ./Core/Src/stream_buffer.cyclo ./Core/Src/stream_buffer.d ./Core/Src/stream_buffer.o ./Core/Src/stream_buffer.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f0xx.cyclo ./Core/Src/system_stm32f0xx.d ./Core/Src/system_stm32f0xx.o ./Core/Src/system_stm32f0xx.su ./Core/Src/tasks.cyclo ./Core/Src/tasks.d ./Core/Src/tasks.o ./Core/Src/tasks.su ./Core/Src/timers.cyclo ./Core/Src/timers.d ./Core/Src/timers.o ./Core/Src/timers.su

.PHONY: clean-Core-2f-Src

