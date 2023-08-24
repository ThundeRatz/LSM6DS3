/**
 * @file platform.cpp
 *
 * @brief This file is a declaration of the Platform_I2C class
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */

#include "platform.hpp"
#include "i2c.h"
#include "gpio.h"
#include "spi.h"

/*****************************************
 * Constants
 *****************************************/

#define LSM6DS_I2C_ADD_H 0xD7U

/*****************************************
 * Public Methods Bodies Definitions
 *****************************************/

int32_t platform_write_I2C(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {
    HAL_I2C_Mem_Write(handle, LSM6DS_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
    return 0;
}

int32_t platform_read_I2C(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {
    HAL_I2C_Mem_Read(handle, LSM6DS_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
    return 0;
}

int32_t platform_write_SPI(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {        
    HAL_GPIO_WritePin(config_settings.SPI_config.cs_gpio_port, config_settings.SPI_config.cs_gpio_port, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &reg, 1, 1000);
    HAL_SPI_Transmit(handle, bufp, len, 1000);
    HAL_GPIO_WritePin(config_settings.SPI_config.cs_gpio_port, config_settings.SPI_config.cs_gpio_port, GPIO_PIN_SET);
    return 0;
}

int32_t platform_read_SPI(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {
     /* MSB must be 1 when reading */
    reg |= 0x80;
    HAL_GPIO_WritePin(config_settings.SPI_config.cs_gpio_port, config_settings.SPI_config.cs_gpio_port, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &reg, 1, 1000);
    HAL_SPI_Receive(handle, bufp, len, 1000);
    HAL_GPIO_WritePin(config_settings.SPI_config.cs_gpio_port, config_settings.SPI_config.cs_gpio_port, GPIO_PIN_SET);
    return 0;
}