#include "platform.h"
#include "main.h" // Pour accéder à hi2c2

extern I2C_HandleTypeDef hi2c2; // On récupère l'instance configurée par l'IOC

uint8_t RdByte(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_value) {
    return HAL_I2C_Mem_Read(p_platform->i2c_handle, p_platform->address, RegisterAddress, I2C_MEMADD_SIZE_16BIT, p_value, 1, 100);
}

uint8_t WrByte(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t value) {
    return HAL_I2C_Mem_Write(p_platform->i2c_handle, p_platform->address, RegisterAddress, I2C_MEMADD_SIZE_16BIT, &value, 1, 100);
}

uint8_t WrMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_values, uint32_t size) {
    return HAL_I2C_Mem_Write(p_platform->i2c_handle, p_platform->address, RegisterAddress, I2C_MEMADD_SIZE_16BIT, p_values, size, 1000);
}

uint8_t RdMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_values, uint32_t size) {
    return HAL_I2C_Mem_Read(p_platform->i2c_handle, p_platform->address, RegisterAddress, I2C_MEMADD_SIZE_16BIT, p_values, size, 1000);
}

void WaitMs(VL53L5CX_Platform *p_platform, uint32_t TimeMs) {
    HAL_Delay(TimeMs);
}
