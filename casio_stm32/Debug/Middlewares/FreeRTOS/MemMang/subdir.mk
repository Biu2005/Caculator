################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FreeRTOS/MemMang/heap_4.c 

OBJS += \
./Middlewares/FreeRTOS/MemMang/heap_4.o 

C_DEPS += \
./Middlewares/FreeRTOS/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/MemMang/%.o Middlewares/FreeRTOS/MemMang/%.su Middlewares/FreeRTOS/MemMang/%.cyclo: ../Middlewares/FreeRTOS/MemMang/%.c Middlewares/FreeRTOS/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/ARM_CM0" -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/include" -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/MemMang" -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-FreeRTOS-2f-MemMang

clean-Middlewares-2f-FreeRTOS-2f-MemMang:
	-$(RM) ./Middlewares/FreeRTOS/MemMang/heap_4.cyclo ./Middlewares/FreeRTOS/MemMang/heap_4.d ./Middlewares/FreeRTOS/MemMang/heap_4.o ./Middlewares/FreeRTOS/MemMang/heap_4.su

.PHONY: clean-Middlewares-2f-FreeRTOS-2f-MemMang

