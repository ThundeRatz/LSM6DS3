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

#include "platform.h"
#include "i2c.h"
#include "spi.h"

/*****************************************
 * Constants
 *****************************************/

#define LSM6DS_I2C_ADD_H 0xD7U

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

int32_t platform_write_I2C(lsm6ds_config_t* I2C_config, uint8_t reg, const uint8_t* bufp, uint16_t len) {
    HAL_I2C_Mem_Write(I2C_config->I2C_pinout.sensor_bus, LSM6DS_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
    return 0;
}

int32_t platform_read_I2C(lsm6ds_config_t* I2C_config, uint8_t reg, uint8_t* bufp, uint16_t len) {
    HAL_I2C_Mem_Read(I2C_config->I2C_pinout.sensor_bus, LSM6DS_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
    return 0;
}

int32_t platform_write_SPI(lsm6ds_config_t* SPI_config, uint8_t reg, const uint8_t* bufp, uint16_t len) {        
    HAL_GPIO_WritePin(SPI_config->SPI_pinout.cs_gpio_port, SPI_config->SPI_pinout.cs_gpio_port, GPIO_PIN_RESET);
    HAL_SPI_Transmit(SPI_config->SPI_pinout.sensor_bus, &reg, 1, 1000);
    HAL_SPI_Transmit(SPI_config->SPI_pinout.sensor_bus, bufp, len, 1000);
    HAL_GPIO_WritePin(SPI_config->SPI_pinout.cs_gpio_port, SPI_config->SPI_pinout.cs_gpio_port, GPIO_PIN_SET);
    return 0;
}

int32_t platform_read_SPI(lsm6ds_config_t* SPI_config, uint8_t reg, uint8_t* bufp, uint16_t len) {
    /* MSB must be 1 when reading */
    reg |= 0x80;
    HAL_GPIO_WritePin((SPI_config->SPI_pinout).cs_gpio_port, (SPI_config->SPI_pinout).cs_gpio_port, GPIO_PIN_RESET);
    HAL_SPI_Transmit(SPI_config->SPI_pinout.sensor_bus, &reg, 1, 1000);
    HAL_SPI_Receive(SPI_config->SPI_pinout.sensor_bus, bufp, len, 1000);
    HAL_GPIO_WritePin((SPI_config->SPI_pinout).cs_gpio_port, (SPI_config->SPI_pinout).cs_gpio_port, GPIO_PIN_SET);
    return 0;
}
