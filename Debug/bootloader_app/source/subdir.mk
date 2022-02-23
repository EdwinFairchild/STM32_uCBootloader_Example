################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bootloader_app/source/bootloader.c 

OBJS += \
./bootloader_app/source/bootloader.o 

C_DEPS += \
./bootloader_app/source/bootloader.d 


# Each subdirectory must supply rules for building sources it contributes
bootloader_app/source/%.o: ../bootloader_app/source/%.c bootloader_app/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/EclipseWorkSpace/STM32_Bootloader/bootloader_app/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-bootloader_app-2f-source

clean-bootloader_app-2f-source:
	-$(RM) ./bootloader_app/source/bootloader.d ./bootloader_app/source/bootloader.o

.PHONY: clean-bootloader_app-2f-source

