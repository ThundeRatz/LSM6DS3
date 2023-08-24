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

#include <iostream>

/*****************************************
 *  Public Types
 *****************************************/

typedef int32_t (*platform_func_t)(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

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
 * 
 * @return error code
 */
int32_t platform_write_I2C(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

/**
 * @brief Platform write register function
 * 
 * @param handle device handle
 * @param reg register to be written
 * @param bufp buffer to be copied
 * @param len length of buffer
 * 
 * @return error code
 */
int32_t platform_write_SPI(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

/**
 * @brief Platform read register function
 * 
 * @param handle device handle
 * @param reg register to be read
 * @param bufp buffer to store read value
 * @param len buffer length
 * 
 * @return error code
 */
int32_t platform_read_I2C(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

/**
 * @brief Platform read register function
 * 
 * @param handle device handle
 * @param reg register to be read
 * @param bufp buffer to store read value
 * @param len buffer length
 * 
 * @return error code
 */
int32_t platform_read_SPI(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);


#endif //__PLATFORM_HPP__