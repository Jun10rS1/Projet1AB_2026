################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery.c \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_audio.c \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_camera.c \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_idd.c \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_io.c \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_lcd.c \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_qspi.c \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sd.c \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sram.c \
../Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_ts.c 

OBJS += \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery.o \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_audio.o \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_camera.o \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_idd.o \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_io.o \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_lcd.o \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_qspi.o \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sd.o \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sram.o \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery.d \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_audio.d \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_camera.d \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_idd.d \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_io.d \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_lcd.d \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_qspi.d \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sd.d \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sram.d \
./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32L496G-Discovery/%.o Drivers/BSP/STM32L496G-Discovery/%.su Drivers/BSP/STM32L496G-Discovery/%.cyclo: ../Drivers/BSP/STM32L496G-Discovery/%.c Drivers/BSP/STM32L496G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/CMSIS/DSP/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32L496G-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32L496G-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery.su ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_audio.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_audio.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_audio.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_audio.su ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_camera.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_camera.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_camera.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_camera.su ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_idd.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_idd.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_idd.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_idd.su ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_io.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_io.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_io.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_io.su ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_lcd.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_lcd.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_lcd.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_lcd.su ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_qspi.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_qspi.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_qspi.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_qspi.su ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sd.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sd.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sd.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sd.su ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sram.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sram.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sram.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_sram.su ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_ts.cyclo ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_ts.d ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_ts.o ./Drivers/BSP/STM32L496G-Discovery/stm32l496g_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32L496G-2d-Discovery

