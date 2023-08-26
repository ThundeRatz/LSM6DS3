/**
 * @file lsm6ds3t-c.hpp
 *
 * @brief This file is a declaration of the LSM6DS3 class
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */

#ifndef __LSM6DS3TRC_PROXY_HPP__
#define __LSM6DS3TRC_PROXY_HPP__

#include "lsm6ds_proxy.hpp"
#include "lsm6ds3tr-c_reg.h"

class LSM6DS3TRC_Proxy : public LSM6DS_Proxy {
    public:
        /**
         * @brief Construct a new LSM6DS3TRC_Proxy object
         * 
         */
        LSM6DS3TRC_Proxy() = default;

        /**
         * @brief Destroy the LSM6DS3TRC_Proxy object
         * 
         */
        ~LSM6DS3TRC_Proxy() = default;

         /**
         * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
         *
         * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
         * @param  I2C_pinout_config  Struct of sensor pinout configurations in I2C mode
         * @param platform_read       Platform read function
         * @param platform_write      Platform write function
         */
        int8_t init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_pinout_t I2C_pinout_config, platform_read_f platform_read, platform_write_f platform_write);

        /**
         * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
         *
         * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
         * @param  SPI_pinout_config  Struct of sensor pinout configurations in SPI mode 
         * @param platform_read       Platform read function
         * @param platform_write      Platform write function
         *
         */
        int8_t init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_pinout_t SPI_pinout_config, platform_read_f platform_read, platform_write_f platform_write);

        /**
         * @brief Update sensor data if available (Use this function if not using interrupt pins)
         */
        void update_data();

        /**
         * @brief Update sensor data (Use this function when using interrupt pins)
         */
        void update_data_ready_interrupt();

        /**
         * @brief Update sensor data (Use this function if using fifo continuous mode with interrupt pins)
         */
        void update_data_fifo_full_interrupt();

        /**
         * @brief Resets fifo data
         */
        void reset_fifo();

        /**
         * @brief Get a pointer to accelerometer data array in mg
         */
        float* get_acc_data_mg();

        /**
         * @brief Get a pointer to gyroscope data array in mdps
         */
        float* get_gyro_data_mdps();

    private:
        /**
         * @brief Base six axis sensor init
         * 
         * @return Error code
         */
        int8_t base_init();

        /**
         * @brief Interrupt mode six axis sensor init
         * 
         * @return Error code 
         */
        int8_t interrupt_init();

        /**
         * @brief Fifo mode six axis sensor init
         * 
         * @return Error code 
         */
        int8_t fifo_mode_init();

        stmdev_ctx_t dev_ctx;
        lsm6ds3tr_c_int1_route_t int_1_reg;
        lsm6ds3tr_c_int2_route_t int_2_reg;
};

#endif // __LSM6DS3TRC_PROXY_HPP__