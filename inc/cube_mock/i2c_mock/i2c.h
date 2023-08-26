/**
 * @file i2c.h
 *
 * @brief This file is a mock file for when "i2c.h" is not defined
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */


#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>

/*****************************************
 *  Constants
 *****************************************/

#define I2C_MEMADD_SIZE_8BIT 0

/*****************************************
 *  Public Functions Bodies Definitions
 *****************************************/

/**
 * @brief Mock Function
 * 
 */
__attribute__((weak)) int32_t HAL_I2C_Mem_Write(void *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, const uint8_t *pData, uint16_t Size, uint32_t Timeout) {}

/**
 * @brief Mock Function
 * 
 */
__attribute__((weak)) int32_t HAL_I2C_Mem_Read(void *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout) {}

#endif