################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../port/source/port.c 

OBJS += \
./port/source/port.o 

C_DEPS += \
./port/source/port.d 


# Each subdirectory must supply rules for building sources it contributes
port/source/%.o: ../port/source/%.c port/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/EclipseWorkSpace/STM32_Bootloader/bootloader_app/include" -I"F:/EclipseWorkSpace/STM32_Bootloader/port/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-port-2f-source

clean-port-2f-source:
	-$(RM) ./port/source/port.d ./port/source/port.o

.PHONY: clean-port-2f-source

