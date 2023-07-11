/**
 * @file lsm6ds.h
 *
 * @brief This file provide functions to get data from the sensor lsm6ds
 *
 * @author Bruno Guo <bruno.guo@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 11/2019
 */

#ifndef LSM6DS3_H
#define LSM6DS3_H

#include <lsm6ds3_reg.h>
#include <lsm6dso_reg.h>

/* Struct of acc/gyro sensitivities and data rates settings */
typedef struct lsm6ds_settings {
    lsm6ds_xl_fs_t  lsm6ds_xl_fs;
    lsm6ds_fs_g_t   lsm6ds_fs_g;
    lsm6ds_odr_xl_t lsm6ds_odr_xl;
    lsm6ds_odr_g_t  lsm6ds_odr_g;
} lsm6ds_settings_t;

/* Error codes */
typedef int8_t LSM6DS_error;
#define LSM6DS_ERROR_NONE ((LSM6DS_error) 0)
#define LSM6DS_ERROR_WHO_AM_I ((LSM6DS_error) 1)
#define LSM6DS_ERROR_WRITE_REGISTER ((LSM6DS_error) 2)

/**
 * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
 *
 * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
 *
 */
int8_t lsm6ds_init(lsm6ds_settings_t lsm6ds_settings);

/**
 * @brief Update sensor data if available (Use this function if not using interrupt pins)
 */
void lsm6ds_update_data();

/**
 * @brief Update sensor data (Use this function when using interrupt pins)
 */
void lsm6ds_update_data_interrupt();

/**
 * @brief Get a pointer to accelerometer data array in mg
 */
float* lsm6ds_get_acc_data_mg();

/**
 * @brief Get a pointer to gyroscope data array in mdps
 */
float* lsm6ds_get_gyro_data_mdps();

/**
 * @brief Get temperature in Celsius
 */
float lsm6ds_get_temperature_degC();

#endif // LSM6DS3_H
