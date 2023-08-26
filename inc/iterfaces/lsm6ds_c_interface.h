/**
 * @file lsm6ds_c_interface.h
 *
 * @brief This file is a declaration for a c compatible interface
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */

#ifndef __LSM6DS_C_INTERFACE_H__
#define __LSM6DS_C_INTERFACE_H__

#include "lsm6ds_settings_type.h"
#include "lsm6ds_pinout.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
 *
 * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
 * @param  I2C_pinout_config  Struct of sensor pinout configurations in I2C mode 
 *
 */
int8_t lsm6ds_init_I2C(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_pinout I2C_pinout_config);

/**
 * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
 *
 * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
 * @param  SPI_pinout_config  Struct of sensor pinout configurations in SPI mode 
 *
 */
int8_t lsm6ds_init_SPI(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_pinout SPI_pinout_config);

/**
 * @brief Update sensor data if available (Use this function if not using interrupt pins)
 */
void lsm6ds_update_data();

/**
 * @brief Update sensor data (Use this function when using interrupt pins)
 */
void lsm6ds_update_data_ready_interrupt();

/**
 * @brief Update sensor data (Use this function if using fifo continuous mode with interrupt pins)
 */
void lsm6ds_update_data_fifo_full_interrupt();

/**
 * @brief Resets fifo data
 */
void lsm6ds_reset_fifo();

/**
 * @brief Get accelerometer data array in mg
 */
float* lsm6ds_get_acc_data_mg();

/**
 * @brief Get gyroscope data array in mdps
 */
float* lsm6ds_get_gyro_data_mdps();

#ifdef __cplusplus
}
#endif

#endif // __LSM6DS_C_INTERFACE_H__