/**
 * @file lsm6ds.hpp
 *
 * @brief This file is a declaration of the LSM6DS class
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 11/2019
 */

#ifndef __LSM6DS_PROXY_HPP__
#define __LSM6DS_PROXY_HPP__

#include <memory>
#include "lsm6ds_settings_type.h"
#include "lsm6ds_common.h"
#include "lsm6ds_pinout.h"
#include "platform.h"

class LSM6DS_Proxy {
    public:
        /**
         * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
         *
         * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
         * @param  I2C_pinout_config  Struct of sensor pinout configurations in I2C mode
         * @param platform_read       Platform read function
         * @param platform_write      Platform write function
         */
        virtual int8_t init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_pinout_t I2C_pinout_config, platform_read_f platform_read, platform_write_f platform_write) = 0;

        /**
         * @brief  Initialize the sensor and set acc/gyro sensitivities and data rate

         *
         * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
         * @param  SPI_pinout_config  Struct of sensor pinout configurations in SPI mode 
         * @param platform_read       Platform read function
         * @param platform_write      Platform write function
         *
         */
        virtual int8_t init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_pinout_t SPI_pinout_config, platform_read_f platform_read, platform_write_f platform_write) = 0;

        /**
         * @brief Update sensor data if available (Use this function if not using interrupt pins)
         */
        virtual void update_data() = 0;

        /**
         * @brief Update sensor data (Use this function when using interrupt pins)
         */
        virtual void update_data_ready_interrupt() = 0;

        /**
         * @brief Update sensor data (Use this function if using fifo continuous mode with interrupt pins)
         */
        virtual void update_data_fifo_full_interrupt() = 0;

        /**
         * @brief Resets fifo data
         */
        virtual void reset_fifo() = 0;

        /**
         * @brief Get a pointer to accelerometer data array in mg
         */
        virtual float get_acc_data_mg() = 0;

        /**
         * @brief Get a pointer to gyroscope data array in mdps
         */
        virtual float get_gyro_data_mdps() = 0;

    protected:
        axis3bit16_t data_raw_acceleration;
        axis3bit16_t data_raw_angular_rate;
        float_t (* acc_conversion_f)(int16_t lsm6ds_xl_fs);
        float_t (* gyro_conversion_f)(int16_t lsm6ds_fs_g);
        lsm6ds_config_t pinout_config;
        float acceleration_mg[3];
        float angular_rate_mdps[3];
};

#endif // __LSM6DS_PROXY_HPP__
