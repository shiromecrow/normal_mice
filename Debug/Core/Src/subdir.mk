################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Control_motor.c \
../Core/Src/Control_sensor.c \
../Core/Src/PID_wall.c \
../Core/Src/PL_lcd.c \
../Core/Src/PL_led.c \
../Core/Src/PL_motor.c \
../Core/Src/PL_sensor.c \
../Core/Src/PL_speaker.c \
../Core/Src/PL_switch.c \
../Core/Src/PL_timer.c \
../Core/Src/adc.c \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/maze_Turning.c \
../Core/Src/maze_strategy.c \
../Core/Src/maze_wall.c \
../Core/Src/mode_selection.c \
../Core/Src/record.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/tim.c \
../Core/Src/turning_parameter.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/Control_motor.o \
./Core/Src/Control_sensor.o \
./Core/Src/PID_wall.o \
./Core/Src/PL_lcd.o \
./Core/Src/PL_led.o \
./Core/Src/PL_motor.o \
./Core/Src/PL_sensor.o \
./Core/Src/PL_speaker.o \
./Core/Src/PL_switch.o \
./Core/Src/PL_timer.o \
./Core/Src/adc.o \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/maze_Turning.o \
./Core/Src/maze_strategy.o \
./Core/Src/maze_wall.o \
./Core/Src/mode_selection.o \
./Core/Src/record.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/tim.o \
./Core/Src/turning_parameter.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/Control_motor.d \
./Core/Src/Control_sensor.d \
./Core/Src/PID_wall.d \
./Core/Src/PL_lcd.d \
./Core/Src/PL_led.d \
./Core/Src/PL_motor.d \
./Core/Src/PL_sensor.d \
./Core/Src/PL_speaker.d \
./Core/Src/PL_switch.d \
./Core/Src/PL_timer.d \
./Core/Src/adc.d \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/maze_Turning.d \
./Core/Src/maze_strategy.d \
./Core/Src/maze_wall.d \
./Core/Src/mode_selection.d \
./Core/Src/record.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/tim.d \
./Core/Src/turning_parameter.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Control_motor.d ./Core/Src/Control_motor.o ./Core/Src/Control_motor.su ./Core/Src/Control_sensor.d ./Core/Src/Control_sensor.o ./Core/Src/Control_sensor.su ./Core/Src/PID_wall.d ./Core/Src/PID_wall.o ./Core/Src/PID_wall.su ./Core/Src/PL_lcd.d ./Core/Src/PL_lcd.o ./Core/Src/PL_lcd.su ./Core/Src/PL_led.d ./Core/Src/PL_led.o ./Core/Src/PL_led.su ./Core/Src/PL_motor.d ./Core/Src/PL_motor.o ./Core/Src/PL_motor.su ./Core/Src/PL_sensor.d ./Core/Src/PL_sensor.o ./Core/Src/PL_sensor.su ./Core/Src/PL_speaker.d ./Core/Src/PL_speaker.o ./Core/Src/PL_speaker.su ./Core/Src/PL_switch.d ./Core/Src/PL_switch.o ./Core/Src/PL_switch.su ./Core/Src/PL_timer.d ./Core/Src/PL_timer.o ./Core/Src/PL_timer.su ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/maze_Turning.d ./Core/Src/maze_Turning.o ./Core/Src/maze_Turning.su ./Core/Src/maze_strategy.d ./Core/Src/maze_strategy.o ./Core/Src/maze_strategy.su ./Core/Src/maze_wall.d ./Core/Src/maze_wall.o ./Core/Src/maze_wall.su ./Core/Src/mode_selection.d ./Core/Src/mode_selection.o ./Core/Src/mode_selection.su ./Core/Src/record.d ./Core/Src/record.o ./Core/Src/record.su ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/turning_parameter.d ./Core/Src/turning_parameter.o ./Core/Src/turning_parameter.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

