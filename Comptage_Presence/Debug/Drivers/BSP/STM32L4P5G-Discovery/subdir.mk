################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery.c \
../Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_idd.c \
../Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_io.c \
../Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_lcd.c \
../Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_mmc.c \
../Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ospi_nor.c \
../Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_psram.c \
../Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ts.c 

OBJS += \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery.o \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_idd.o \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_io.o \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_lcd.o \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_mmc.o \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ospi_nor.o \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_psram.o \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery.d \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_idd.d \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_io.d \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_lcd.d \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_mmc.d \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ospi_nor.d \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_psram.d \
./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32L4P5G-Discovery/%.o Drivers/BSP/STM32L4P5G-Discovery/%.su Drivers/BSP/STM32L4P5G-Discovery/%.cyclo: ../Drivers/BSP/STM32L4P5G-Discovery/%.c Drivers/BSP/STM32L4P5G-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/CMSIS/DSP/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32L4P5G-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32L4P5G-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery.cyclo ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery.d ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery.o ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery.su ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_idd.cyclo ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_idd.d ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_idd.o ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_idd.su ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_io.cyclo ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_io.d ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_io.o ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_io.su ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_lcd.cyclo ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_lcd.d ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_lcd.o ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_lcd.su ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_mmc.cyclo ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_mmc.d ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_mmc.o ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_mmc.su ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ospi_nor.cyclo ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ospi_nor.d ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ospi_nor.o ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ospi_nor.su ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_psram.cyclo ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_psram.d ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_psram.o ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_psram.su ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ts.cyclo ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ts.d ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ts.o ./Drivers/BSP/STM32L4P5G-Discovery/stm32l4p5g_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32L4P5G-2d-Discovery

