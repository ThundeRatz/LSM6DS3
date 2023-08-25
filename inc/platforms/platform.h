/**
 * @file platform.hpp
 *
 * @brief This file is a declaration of the Platform class
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */
        
#ifndef __PLATFORM_HPP__
#define __PLATFORM_HPP__

#include "lsm6ds_pinout.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************
 *  Public Types
 *****************************************/

typedef int32_t (*platform_write_f)(void* handle, uint8_t reg, const uint8_t* bufp, uint16_t len, lsm6ds_config_t* SPI_config);
typedef int32_t (*platform_read_f)(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len, lsm6ds_config_t* SPI_config);

/*****************************************
 *  Public Functions Declaration
 *****************************************/

/**
 * @brief Platform write register function
 * 
 * @param handle device handle
 * @param reg register to be written
 * @param bufp buffer to be copied
 * @param len length of buffer
 * @param I2C_config Structure containing pinout information
 * 
 * @return error code
 */
int32_t platform_write_I2C(void* handle, uint8_t reg, const uint8_t* bufp, uint16_t len, lsm6ds_config_t* I2C_config);

/**
 * @brief Platform write register function
 * 
 * @param handle device handle
 * @param reg register to be written
 * @param bufp buffer to be copied
 * @param len length of buffer
 * @param SPI_config Structure containing pinout information
 * 
 * @return error code
 */
int32_t platform_write_SPI(void* handle, uint8_t reg, const uint8_t* bufp, uint16_t len, lsm6ds_config_t* SPI_config);

/**
 * @brief Platform read register function
 * 
 * @param handle device handle
 * @param reg register to be read
 * @param bufp buffer to store read value
 * @param len buffer length
 * @param I2C_config Structure containing pinout information
 * 
 * @return error code
 */
int32_t platform_read_I2C(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len, lsm6ds_config_t* I2C_config);

/**
 * @brief Platform read register function
 * 
 * @param handle device handle
 * @param reg register to be read
 * @param bufp buffer to store read value
 * @param len buffer length
 * @param SPI_config Structure containing pinout information
 * 
 * @return error code
 */
int32_t platform_read_SPI(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len, lsm6ds_config_t* SPI_config);

#ifdef __cplusplus
}
#endif

#endif //__PLATFORM_HPP__