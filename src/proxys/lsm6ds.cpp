/**
 * @file lsm6ds.cpp
 *
 * @brief This file provide functions to get data from the sensor lsm6ds
 *
 * @author Bruno Guo <bruno.guo@thunderatz.org>
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 *
 * @date 08/2023
 */

#include "lsm6ds.hpp"
#include "lsm6ds3.hpp"
#include "lsm6ds3tr-c.hpp"
#include "lsm6dso.hpp"
#include "gpio.h"
#include "i2c.h"
#include "spi.h"
#include <cstring>

/*****************************************
 * CONSTANTS
 *****************************************/

#define WHO_AM_I_ID 0x0FU
#define LSM6DS3TRC_ID 0x6AU
#define LSM6DSO_ID 0x6C
#define LSM6DS3_ID 0x69U
#define LSM6DS_I2C_ADD_H 0xD7U

/*****************************************
 * Class Public Methods Bodies Definitions
 *****************************************/

int8_t LSM6DS::init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_config I2C_pinout_config) {
    int32_t rst;
    int8_t whoamI;
    config_settings.I2C_config = I2C_pinout_config;
    serial_type = LSM6DS_I2C;
    rst =  platform_read(I2C_pinout_config.sensor_bus, WHO_AM_I_ID, (uint8_t*)&whoamI, sizeof(int8_t));
    
    if (rst != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    switch (whoamI) {
        case(LSM6DS3_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DS3>();
            return lsm6ds_sensor->init(lsm6ds_settings, I2C_pinout_config);
        }
        case(LSM6DS3TRC_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DS3TRC>();
            return lsm6ds_sensor->init(lsm6ds_settings, I2C_pinout_config);
        }
        case(LSM6DSO_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DSO>();
            return lsm6ds_sensor->init(lsm6ds_settings, I2C_pinout_config);   
        }
        default: {
            return LSM6DS_ERROR_WHO_AM_I;
        }
    }
}

int8_t LSM6DS::init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_config SPI_pinout_config) {
    int32_t rst;
    int8_t whoamI;
    config_settings.SPI_config = SPI_pinout_config;
    serial_type = LSM6DS_I2C;
    rst =  platform_read(SPI_pinout_config.sensor_bus, WHO_AM_I_ID, (uint8_t*)&whoamI, sizeof(int8_t));
    
    if (rst != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    switch (whoamI) {
        case(LSM6DS3_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DS3>();
            return lsm6ds_sensor->init(lsm6ds_settings, SPI_pinout_config);
        }
        case(LSM6DS3TRC_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DS3TRC>();
            return lsm6ds_sensor->init(lsm6ds_settings, SPI_pinout_config);
        }
        case(LSM6DSO_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DSO>();
            return lsm6ds_sensor->init(lsm6ds_settings, SPI_pinout_config);   
        }
        default: {
            return LSM6DS_ERROR_WHO_AM_I;
        }
    }
}

void LSM6DS::update_data() {
    lsm6ds_sensor->update_data();
}

void LSM6DS::update_data_ready_interrupt() {
    lsm6ds_sensor->update_data_ready_interrupt();
}

void LSM6DS::update_data_fifo_full_interrupt() {
    lsm6ds_sensor->update_data_fifo_full_interrupt();
}

void LSM6DS::reset_fifo() {
    lsm6ds_sensor->reset_fifo();
}

float LSM6DS::get_acc_data_mg() {
    return lsm6ds_sensor->get_acc_data_mg();
}

float LSM6DS::get_gyro_data_mdps() {
    return lsm6ds_sensor->get_gyro_data_mdps();
}

/*****************************************
 * Class Public Methods Bodies Definitions
 *****************************************/

int32_t LSM6DS::platform_write(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {
    switch(serial_type) {
        case LSM6DS_I2C: {
            return platform_write_I2C(handle, reg, bufp, len);
        }
        case LSM6DS_SPI: {
            return platform_write_SPI(handle, reg, bufp, len);
        }
        default: {
            return LSM6DS_ERROR_NO_INIT;
        }
    }
}

int32_t LSM6DS::platform_write_I2C(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {
    HAL_I2C_Mem_Write(handle, LSM6DS_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
    return 0;
}

int32_t LSM6DS::platform_write_SPI(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {        
    HAL_GPIO_WritePin(config_settings.SPI_config.cs_gpio_port, config_settings.SPI_config.cs_gpio_port, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &reg, 1, 1000);
    HAL_SPI_Transmit(handle, bufp, len, 1000);
    HAL_GPIO_WritePin(config_settings.SPI_config.cs_gpio_port, config_settings.SPI_config.cs_gpio_port, GPIO_PIN_SET);
    return 0;
}

int32_t LSM6DS::platform_read(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {
    switch(serial_type) {
        case LSM6DS_I2C: {
            return platform_read_I2C(handle, reg, bufp, len);
        }
        case LSM6DS_SPI: {
            return platform_read_SPI(handle, reg, bufp, len);
        }
        default: {
            return LSM6DS_ERROR_NO_INIT;
        }
    }
}

int32_t LSM6DS::platform_read_I2C(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {
        HAL_I2C_Mem_Read(handle, LSM6DS_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
        return 0;
}

int32_t LSM6DS::platform_read_SPI(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len) {
     /* MSB must be 1 when reading */
        reg |= 0x80;
        HAL_GPIO_WritePin(config_settings.SPI_config.cs_gpio_port, config_settings.SPI_config.cs_gpio_port, GPIO_PIN_RESET);
        HAL_SPI_Transmit(handle, &reg, 1, 1000);
        HAL_SPI_Receive(handle, bufp, len, 1000);
        HAL_GPIO_WritePin(config_settings.SPI_config.cs_gpio_port, config_settings.SPI_config.cs_gpio_port, GPIO_PIN_SET);
        return 0;
}
