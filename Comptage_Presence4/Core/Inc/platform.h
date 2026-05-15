#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <stdint.h>

// Nombre de cibles par zone (1 est le standard pour le pilote Ultra Lite)
#define VL53L5CX_NB_TARGET_PER_ZONE    1U

typedef struct {
    uint16_t  address;
    void      *i2c_handle;
} VL53L5CX_Platform;

// Nouveaux prototypes avec le préfixe VL53L5CX_
uint8_t VL53L5CX_RdByte(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_value);
uint8_t VL53L5CX_WrByte(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t value);
uint8_t VL53L5CX_WrMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_values, uint32_t size);
uint8_t VL53L5CX_RdMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_values, uint32_t size);
uint8_t VL53L5CX_WaitMs(VL53L5CX_Platform *p_platform, uint32_t TimeMs);

// Ajoute cette ligne avec les autres prototypes
uint8_t VL53L5CX_SwapBuffer(uint8_t *buffer, uint16_t size);

#endif
