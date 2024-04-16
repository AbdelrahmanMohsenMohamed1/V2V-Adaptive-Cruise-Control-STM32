################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/BUZZER_program.c \
../Core/Src/DC_MOT.c \
../Core/Src/HC05_Bluetooth.c \
../Core/Src/LCD_program.c \
../Core/Src/LED_program.c \
../Core/Src/UltraSonic_program_.c \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/BUZZER_program.o \
./Core/Src/DC_MOT.o \
./Core/Src/HC05_Bluetooth.o \
./Core/Src/LCD_program.o \
./Core/Src/LED_program.o \
./Core/Src/UltraSonic_program_.o \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/BUZZER_program.d \
./Core/Src/DC_MOT.d \
./Core/Src/HC05_Bluetooth.d \
./Core/Src/LCD_program.d \
./Core/Src/LED_program.d \
./Core/Src/UltraSonic_program_.d \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/BUZZER_program.cyclo ./Core/Src/BUZZER_program.d ./Core/Src/BUZZER_program.o ./Core/Src/BUZZER_program.su ./Core/Src/DC_MOT.cyclo ./Core/Src/DC_MOT.d ./Core/Src/DC_MOT.o ./Core/Src/DC_MOT.su ./Core/Src/HC05_Bluetooth.cyclo ./Core/Src/HC05_Bluetooth.d ./Core/Src/HC05_Bluetooth.o ./Core/Src/HC05_Bluetooth.su ./Core/Src/LCD_program.cyclo ./Core/Src/LCD_program.d ./Core/Src/LCD_program.o ./Core/Src/LCD_program.su ./Core/Src/LED_program.cyclo ./Core/Src/LED_program.d ./Core/Src/LED_program.o ./Core/Src/LED_program.su ./Core/Src/UltraSonic_program_.cyclo ./Core/Src/UltraSonic_program_.d ./Core/Src/UltraSonic_program_.o ./Core/Src/UltraSonic_program_.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

