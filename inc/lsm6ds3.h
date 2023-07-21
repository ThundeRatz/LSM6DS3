/**
 * @file lsm6ds3.h
 *
 * @brief This file provide functions to get data from the sensor lsm6ds3
 *
 * @author Bruno Guo <bruno.guo@thunderatz.org>
 *
 * @date 11/2019
 */

#ifndef LSM6DS3_H
#define LSM6DS3_H

#include <lsm6ds3_reg.h>

/* Struct of acc/gyro sensitivities and data rates settings */
typedef struct lsm6ds3_settings {
    lsm6ds3_xl_fs_t  lsm6ds3_xl_fs;
    lsm6ds3_fs_g_t   lsm6ds3_fs_g;
    lsm6ds3_odr_xl_t lsm6ds3_odr_xl;
    lsm6ds3_odr_g_t  lsm6ds3_odr_g;
    lsm6ds3_fifo_md_t lsm6ds3_fifo_md;
    lsm6ds3_odr_fifo_t lsm6ds3_odr_fifo;
    lsm6ds3_dec_fifo_gyro_t lsm6ds3_dec_fifo_gyro;
    lsm6ds3_dec_fifo_xl_t lsm6ds3_dec_fifo_xl;
    uint16_t lsm6ds3_threshold_fifo;
} lsm6ds3_settings_t;

/* Error codes */
typedef int8_t LSM6DS3_error;
#define LSM6DS3_ERROR_NONE ((LSM6DS3_error) 0)
#define LSM6DS3_ERROR_WHO_AM_I ((LSM6DS3_error) 1)
#define LSM6DS3_ERROR_WRITE_REGISTER ((LSM6DS3_error) 2)

/**
 * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
 *
 * @param  lsm6ds3_settings    Struct of acc/gyro sensitivities and data rates settings
 *
 */
int8_t lsm6ds3_init(lsm6ds3_settings_t lsm6ds3_settings);

/**
 * @brief Update sensor data if available (Use this function if not using interrupt pins)
 */
void lsm6ds3_update_data();

/**
 * @brief Update sensor data (Use this function when using interrupt pins)
 */
void lsm6ds3_update_data_interrupt();

/**
 * @brief Get a pointer to accelerometer data array in mg
 */
float* lsm6ds3_get_acc_data_mg();

/**
 * @brief Get a pointer to gyroscope data array in mdps
 */
float* lsm6ds3_get_gyro_data_mdps();

/**
 * @brief Get temperature in Celsius
 */
float lsm6ds3_get_temperature_degC();

#endif // LSM6DS3_H
