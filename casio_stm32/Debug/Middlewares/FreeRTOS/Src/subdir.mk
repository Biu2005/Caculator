################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FreeRTOS/Src/croutine.c \
../Middlewares/FreeRTOS/Src/event_groups.c \
../Middlewares/FreeRTOS/Src/list.c \
../Middlewares/FreeRTOS/Src/queue.c \
../Middlewares/FreeRTOS/Src/stream_buffer.c \
../Middlewares/FreeRTOS/Src/tasks.c \
../Middlewares/FreeRTOS/Src/timers.c 

OBJS += \
./Middlewares/FreeRTOS/Src/croutine.o \
./Middlewares/FreeRTOS/Src/event_groups.o \
./Middlewares/FreeRTOS/Src/list.o \
./Middlewares/FreeRTOS/Src/queue.o \
./Middlewares/FreeRTOS/Src/stream_buffer.o \
./Middlewares/FreeRTOS/Src/tasks.o \
./Middlewares/FreeRTOS/Src/timers.o 

C_DEPS += \
./Middlewares/FreeRTOS/Src/croutine.d \
./Middlewares/FreeRTOS/Src/event_groups.d \
./Middlewares/FreeRTOS/Src/list.d \
./Middlewares/FreeRTOS/Src/queue.d \
./Middlewares/FreeRTOS/Src/stream_buffer.d \
./Middlewares/FreeRTOS/Src/tasks.d \
./Middlewares/FreeRTOS/Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/Src/%.o Middlewares/FreeRTOS/Src/%.su Middlewares/FreeRTOS/Src/%.cyclo: ../Middlewares/FreeRTOS/Src/%.c Middlewares/FreeRTOS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/ARM_CM0" -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/include" -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/MemMang" -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-FreeRTOS-2f-Src

clean-Middlewares-2f-FreeRTOS-2f-Src:
	-$(RM) ./Middlewares/FreeRTOS/Src/croutine.cyclo ./Middlewares/FreeRTOS/Src/croutine.d ./Middlewares/FreeRTOS/Src/croutine.o ./Middlewares/FreeRTOS/Src/croutine.su ./Middlewares/FreeRTOS/Src/event_groups.cyclo ./Middlewares/FreeRTOS/Src/event_groups.d ./Middlewares/FreeRTOS/Src/event_groups.o ./Middlewares/FreeRTOS/Src/event_groups.su ./Middlewares/FreeRTOS/Src/list.cyclo ./Middlewares/FreeRTOS/Src/list.d ./Middlewares/FreeRTOS/Src/list.o ./Middlewares/FreeRTOS/Src/list.su ./Middlewares/FreeRTOS/Src/queue.cyclo ./Middlewares/FreeRTOS/Src/queue.d ./Middlewares/FreeRTOS/Src/queue.o ./Middlewares/FreeRTOS/Src/queue.su ./Middlewares/FreeRTOS/Src/stream_buffer.cyclo ./Middlewares/FreeRTOS/Src/stream_buffer.d ./Middlewares/FreeRTOS/Src/stream_buffer.o ./Middlewares/FreeRTOS/Src/stream_buffer.su ./Middlewares/FreeRTOS/Src/tasks.cyclo ./Middlewares/FreeRTOS/Src/tasks.d ./Middlewares/FreeRTOS/Src/tasks.o ./Middlewares/FreeRTOS/Src/tasks.su ./Middlewares/FreeRTOS/Src/timers.cyclo ./Middlewares/FreeRTOS/Src/timers.d ./Middlewares/FreeRTOS/Src/timers.o ./Middlewares/FreeRTOS/Src/timers.su

.PHONY: clean-Middlewares-2f-FreeRTOS-2f-Src

