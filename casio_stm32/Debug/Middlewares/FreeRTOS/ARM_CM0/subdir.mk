################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FreeRTOS/ARM_CM0/mpu_wrappers_v2_asm.c \
../Middlewares/FreeRTOS/ARM_CM0/port.c \
../Middlewares/FreeRTOS/ARM_CM0/portasm.c 

OBJS += \
./Middlewares/FreeRTOS/ARM_CM0/mpu_wrappers_v2_asm.o \
./Middlewares/FreeRTOS/ARM_CM0/port.o \
./Middlewares/FreeRTOS/ARM_CM0/portasm.o 

C_DEPS += \
./Middlewares/FreeRTOS/ARM_CM0/mpu_wrappers_v2_asm.d \
./Middlewares/FreeRTOS/ARM_CM0/port.d \
./Middlewares/FreeRTOS/ARM_CM0/portasm.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/ARM_CM0/%.o Middlewares/FreeRTOS/ARM_CM0/%.su Middlewares/FreeRTOS/ARM_CM0/%.cyclo: ../Middlewares/FreeRTOS/ARM_CM0/%.c Middlewares/FreeRTOS/ARM_CM0/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x6 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/ARM_CM0" -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/include" -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/MemMang" -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-FreeRTOS-2f-ARM_CM0

clean-Middlewares-2f-FreeRTOS-2f-ARM_CM0:
	-$(RM) ./Middlewares/FreeRTOS/ARM_CM0/mpu_wrappers_v2_asm.cyclo ./Middlewares/FreeRTOS/ARM_CM0/mpu_wrappers_v2_asm.d ./Middlewares/FreeRTOS/ARM_CM0/mpu_wrappers_v2_asm.o ./Middlewares/FreeRTOS/ARM_CM0/mpu_wrappers_v2_asm.su ./Middlewares/FreeRTOS/ARM_CM0/port.cyclo ./Middlewares/FreeRTOS/ARM_CM0/port.d ./Middlewares/FreeRTOS/ARM_CM0/port.o ./Middlewares/FreeRTOS/ARM_CM0/port.su ./Middlewares/FreeRTOS/ARM_CM0/portasm.cyclo ./Middlewares/FreeRTOS/ARM_CM0/portasm.d ./Middlewares/FreeRTOS/ARM_CM0/portasm.o ./Middlewares/FreeRTOS/ARM_CM0/portasm.su

.PHONY: clean-Middlewares-2f-FreeRTOS-2f-ARM_CM0

