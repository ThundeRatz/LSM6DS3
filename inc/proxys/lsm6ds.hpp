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

#ifndef LSM6DS_H
#define LSM6DS_H

#include <memory>
#include "lsm6ds_settings_type.hpp"
#include "lsm6ds_common.hpp"
#include "lsm6ds_pinout.hpp"

class LSM6DS {
    public:
        /**
         * @brief Construct a new LSM6DS object
         * 
         */
        LSM6DS() = default;

        /**
         * @brief Destroy the LSM6DS object
         * 
         */
        ~LSM6DS();

        /**
         * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
         *
         * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
         * @param  I2C_pinout_config  Struct of sensor pinout configurations in I2C mode 
         *
         */
        virtual int8_t init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_config I2C_pinout_config);

        /**
         * @brief  Initialize the sensor and set acc/gyro sensitivities and data rates
         *
         * @param  lsm6ds_settings    Struct of acc/gyro sensitivities and data rates settings
         * @param  SPI_pinout_config  Struct of sensor pinout configurations in SPI mode 
         *
         */
        virtual int8_t init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_config SPI_pinout_config);

        /**
         * @brief Update sensor data if available (Use this function if not using interrupt pins)
         */
        virtual void update_data();

        /**
         * @brief Update sensor data (Use this function when using interrupt pins)
         */
        virtual void update_data_ready_interrupt();

        /**
         * @brief Update sensor data (Use this function if using fifo continuous mode with interrupt pins)
         */
        virtual void update_data_fifo_full_interrupt();

        /**
         * @brief Resets fifo data
         */
        virtual void reset_fifo();

        /**
         * @brief Get a pointer to accelerometer data array in mg
         */
        virtual float get_acc_data_mg();

        /**
         * @brief Get a pointer to gyroscope data array in mdps
         */
        virtual float get_gyro_data_mdps();
  
    protected:
        /**
         * @brief Platform write register function
         * 
         * @param handle device handle
         * @param reg register to be written
         * @param bufp buffer to be copied
         * @param len length of buffer
         * 
         * @return error code
         */
        int32_t platform_write(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

        /**
         * @brief Platform write register function
         * 
         * @param handle device handle
         * @param reg register to be written
         * @param bufp buffer to be copied
         * @param len length of buffer
         * 
         * @return error code
         */
        int32_t platform_write_I2C(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

        /**
         * @brief Platform write register function
         * 
         * @param handle device handle
         * @param reg register to be written
         * @param bufp buffer to be copied
         * @param len length of buffer
         * 
         * @return error code
         */
        int32_t platform_write_SPI(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

        /**
         * @brief Platform read register function
         * 
         * @param handle device handle
         * @param reg register to be read
         * @param bufp buffer to store read value
         * @param len buffer length
         * 
         * @return error code
         */
        int32_t platform_read(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

        /**
         * @brief Platform read register function
         * 
         * @param handle device handle
         * @param reg register to be read
         * @param bufp buffer to store read value
         * @param len buffer length
         * 
         * @return error code
         */
        int32_t platform_read_I2C(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

        /**
         * @brief Platform read register function
         * 
         * @param handle device handle
         * @param reg register to be read
         * @param bufp buffer to store read value
         * @param len buffer length
         * 
         * @return error code
         */
        int32_t platform_read_SPI(void* handle, uint8_t reg, uint8_t* bufp, uint16_t len);

        lsm6ds_config config_settings;
        lsm6ds_serial_type_t serial_type;

    private:
        std::unique_ptr<LSM6DS> lsm6ds_sensor;
};

#endif // LSM6DS_H
