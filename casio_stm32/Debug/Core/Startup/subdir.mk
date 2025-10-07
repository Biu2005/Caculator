################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f030k6tx.s 

OBJS += \
./Core/Startup/startup_stm32f030k6tx.o 

S_DEPS += \
./Core/Startup/startup_stm32f030k6tx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -DDEBUG -c -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/ARM_CM0" -I../Core/Inc -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/include" -I"D:/altium and source projects/source_casio/casio_stm32/Middlewares/FreeRTOS/MemMang" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f030k6tx.d ./Core/Startup/startup_stm32f030k6tx.o

.PHONY: clean-Core-2f-Startup

