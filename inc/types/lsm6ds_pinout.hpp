/**
 * @file lsm6ds_pinout.hpp
 *
 * @brief IMU pinout settings.
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 *
 * @date 08/2023
 */

#ifndef __LSM6DS_PINOUT_HPP__
#define __LSM6DS_PINOUT_HPP__

#include <iostream>

typedef enum lsm6ds_serial_type {
    LSM6DS_I2C,
    LSM6DS_SPI
} lsm6ds_serial_type_t;

typedef struct lsm6ds_I2C_config {
    void (*I2C_init)();
    void* sensor_bus;
    uint8_t int1_pin;
    uint8_t int1_port;
    uint8_t int2_pin;
    uint8_t int2_port;
} lsm6ds_I2C_config_t;  

typedef struct lsm6ds_SPI_config {
    void (*SPI_init)();
    void* sensor_bus;
    uint8_t cs_gpio_port;
    uint8_t cs_gpio_pin;
    uint8_t int1_pin;
    uint8_t int1_port;
    uint8_t int2_pin;
    uint8_t int2_port;
} lsm6ds_SPI_config_t;

typedef union lsm6ds_config {
    lsm6ds_I2C_config_t I2C_config;
    lsm6ds_SPI_config_t SPI_config;
} lsm6ds_config_t;

#endif // __LSM6DS_PINOUT_HPP__