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

typedef struct lsm6ds_I2C_pinout {
    uint8_t int1_pin;
    uint8_t int1_port;
    uint8_t int2_pin;
    uint8_t int2_port;
    void (*I2C_init)();
    void* sensor_bus;
} lsm6ds_I2C_pinout_t;  

typedef struct lsm6ds_SPI_pinout {
    uint8_t int1_pin;
    uint8_t int1_port;
    uint8_t int2_pin;
    uint8_t int2_port;
    uint8_t cs_gpio_port;
    uint8_t cs_gpio_pin;
    void (*SPI_init)();
    void* sensor_bus;
} lsm6ds_SPI_pinout_t;

typedef  struct lsm6ds_common_pinout {
    uint8_t int1_pin;
    uint8_t int1_port;
    uint8_t int2_pin;
    uint8_t int2_port;
} lsm6ds_common_pinout;

typedef union lsm6ds_config {
    lsm6ds_I2C_pinout_t I2C_pinout;
    lsm6ds_SPI_pinout_t SPI_pinout;
    lsm6ds_common_pinout common_pinout;
} lsm6ds_config_t;

#ifdef __cplusplus
}
#endif

#endif // __LSM6DS_PINOUT_H__