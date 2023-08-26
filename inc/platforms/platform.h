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

#include "i2c.h"
#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************
 *  Public Types
 *****************************************/

typedef int32_t (*platform_write_f)(lsm6ds_config_t* pinout_config, uint8_t reg, const uint8_t* bufp, uint16_t len);
typedef int32_t (*platform_read_f)(lsm6ds_config_t* pinout_config, uint8_t reg, uint8_t* bufp, uint16_t len);

/*****************************************
 *  Public Functions Declaration
 *****************************************/

/**
 * @brief Platform write register function
 * 
 * @param I2C_config Structure containing pinout information
 * @param reg register to be written
 * @param bufp buffer to be copied
 * @param len length of buffer
 * 
 * @return error code
 */
int32_t platform_write_I2C(lsm6ds_config_t* I2C_config, uint8_t reg, const uint8_t* bufp, uint16_t len);

/**
 * @brief Platform write register function
 * 
 * @param SPI_config Structure containing pinout information
 * @param reg register to be written
 * @param bufp buffer to be copied
 * @param len length of buffer
 * 
 * @return error code
 */
int32_t platform_write_SPI(lsm6ds_config_t* SPI_config, uint8_t reg, const uint8_t* bufp, uint16_t len);

/**
 * @brief Platform read register function
 * 
 * @param I2C_config Structure containing pinout information
 * @param reg register to be read
 * @param bufp buffer to store read value
 * @param len buffer length
 * 
 * @return error code
 */
int32_t platform_read_I2C(lsm6ds_config_t* I2C_config, uint8_t reg, uint8_t* bufp, uint16_t len);

/**
 * @brief Platform read register function
 * 
 * @param SPI_config Structure containing pinout information
 * @param reg register to be read
 * @param bufp buffer to store read value
 * @param len buffer length
 * 
 * @return error code
 */
int32_t platform_read_SPI(lsm6ds_config_t* SPI_config, uint8_t reg, uint8_t* bufp, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif //__PLATFORM_HPP__