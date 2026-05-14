#include "platform.h"
#include "stm32g4xx_hal.h"

extern I2C_HandleTypeDef hi2c2;

uint8_t VL53L5CX_RdByte(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_value) {
    return HAL_I2C_Mem_Read(&hi2c2, p_platform->address, RegisterAddress, I2C_MEMADD_SIZE_16BIT, p_value, 1, HAL_MAX_DELAY);
}

uint8_t VL53L5CX_WrByte(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t value) {
    return HAL_I2C_Mem_Write(&hi2c2, p_platform->address, RegisterAddress, I2C_MEMADD_SIZE_16BIT, &value, 1, HAL_MAX_DELAY);
}

uint8_t VL53L5CX_WrMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_values, uint32_t size) {
    return HAL_I2C_Mem_Write(&hi2c2, p_platform->address, RegisterAddress, I2C_MEMADD_SIZE_16BIT, p_values, size, HAL_MAX_DELAY);
}

uint8_t VL53L5CX_RdMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_values, uint32_t size) {
    return HAL_I2C_Mem_Read(&hi2c2, p_platform->address, RegisterAddress, I2C_MEMADD_SIZE_16BIT, p_values, size, HAL_MAX_DELAY);
}

uint8_t VL53L5CX_WaitMs(VL53L5CX_Platform *p_platform, uint32_t TimeMs) {
    HAL_Delay(TimeMs);
    return 0;
}

uint8_t VL53L5CX_SwapBuffer(uint8_t *buffer, uint16_t size) {
    uint32_t i;
    uint8_t tmp;
    for(i = 0; i < size; i = i + 4) {
        tmp = buffer[i];
        buffer[i] = buffer[i+3];
        buffer[i+3] = tmp;
        tmp = buffer[i+1];
        buffer[i+1] = buffer[i+2];
        buffer[i+2] = tmp;
    }
    return 0;
}
