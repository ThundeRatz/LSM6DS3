/**
 * @file lsm6ds_pinout.h
 *
 * @brief IMU pinout settings.
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 *
 * @date 08/2023
 */

#ifndef __LSM6DS_PINOUT_H__
#define __LSM6DS_PINOUT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum lsm6ds_serial_type {
    LSM6DS_I2C,
    LSM6DS_SPI
} lsm6ds_serial_type_t;

typedef struct lsm6ds_I2C_pinout {
    void (*I2C_init)();
    void* sensor_bus;
    uint8_t int1_pin;
    uint8_t int1_port;
    uint8_t int2_pin;
    uint8_t int2_port;
} lsm6ds_I2C_pinout_t;  

typedef struct lsm6ds_SPI_pinout {
    void (*SPI_init)();
    void* sensor_bus;
    uint8_t cs_gpio_port;
    uint8_t cs_gpio_pin;
    uint8_t int1_pin;
    uint8_t int1_port;
    uint8_t int2_pin;
    uint8_t int2_port;
} lsm6ds_SPI_pinout_t;

typedef union lsm6ds_config {
    lsm6ds_I2C_pinout_t I2C_pinout;
    lsm6ds_SPI_pinout_t SPI_pinout;
} lsm6ds_config_t;

#ifdef __cplusplus
}
#endif

#endif // __LSM6DS_PINOUT_H__