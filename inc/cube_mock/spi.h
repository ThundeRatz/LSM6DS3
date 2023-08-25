/**
 * @file spi.h
 *
 * @brief This file is a mock file for when "spi.h" is not defined
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */

#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

/*****************************************
 *  Constants
 *****************************************/

#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1

/*****************************************
 *  Public Functions Bodies Definitions
 *****************************************/

/**
 * @brief Mock Function
 * 
 */
int32_t HAL_GPIO_WritePin(uint8_t, uint8_t, bool) {}

/**
 * @brief Mock Function
 * 
 */
int32_t HAL_SPI_Transmit(void* , const uint8_t*, uint16_t, int32_t) {}

/**
 * @brief Mock Function
 * 
 */
int32_t HAL_SPI_Receive(void* , uint8_t*, uint16_t, int32_t) {}

#endif