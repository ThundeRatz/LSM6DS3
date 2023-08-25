/**
 * @file lsm6ds_interface.hpp
 *
 * @brief This file is a declaration of the LSM6DS class
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */

#ifndef __LSM6DS_INTERFACE_HPP__
#define __LSM6DS_INTERFACE_HPP__

#include "lsm6ds_proxy.hpp"

class LSM6DS_Interface {
    public:
        /**
         * @brief Construct a new LSM6DS_Interface object
         * 
         */
        LSM6DS_Interface() = default;

        /**
         * @brief Destroy the LSM6DS_Interface object
         * 
         */
        ~LSM6DS_Interface() = default;

        /**
         * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
         *
         * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
         * @param  I2C_pinout_config  Struct of sensor pinout configurations in I2C mode 
         *
         */
        int8_t init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_pinout I2C_pinout_config);

        /**
         * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
         *
         * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
         * @param  SPI_pinout_config  Struct of sensor pinout configurations in SPI mode 
         *
         */
        int8_t init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_pinout SPI_pinout_config);

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
         * @brief Get accelerometer data array in mg
         */
        float get_acc_data_mg();

        /**
         * @brief Get gyroscope data array in mdps
         */
        float get_gyro_data_mdps();
  
    private:
        std::unique_ptr<LSM6DS_Proxy> lsm6ds_sensor;
};

#endif // __LSM6DS_INTERFACE_HPP__
