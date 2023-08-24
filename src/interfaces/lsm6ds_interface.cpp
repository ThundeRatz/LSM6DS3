/**
 * @file lsm6ds.cpp
 *
 * @brief This file provide functions to get data from the sensor lsm6ds
 *
 * @author Bruno Guo <bruno.guo@thunderatz.org>
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 *
 * @date 08/2023
 */

#include "lsm6ds_interface.hpp"
#include "lsm6ds3_proxy.hpp"
#include "lsm6ds3tr-c_proxy.hpp"
#include "lsm6dso_proxy.hpp"
#include "platform.hpp"
#include <cstring>

/*****************************************
 * Constants
 *****************************************/

#define WHO_AM_I_ID 0x0FU
#define LSM6DS3TRC_ID 0x6AU
#define LSM6DSO_ID 0x6C
#define LSM6DS3_ID 0x69U

/*****************************************
 * Class Public Methods Bodies Definitions
 *****************************************/

int8_t LSM6DS_Interface::init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_config I2C_pinout_config) {
    int32_t rst;
    int8_t whoamI;
    rst =  platform_read_I2C(I2C_pinout_config.sensor_bus, WHO_AM_I_ID, (uint8_t*)&whoamI, sizeof(int8_t));
    
    if (rst != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    switch (whoamI) {
        case(LSM6DS3_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DS3_Proxy>();
            return lsm6ds_sensor->init(lsm6ds_settings, I2C_pinout_config, platform_read_I2C, platform_write_I2C);
        }
        case(LSM6DS3TRC_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DS3TRC_Proxy>();
            return lsm6ds_sensor->init(lsm6ds_settings, I2C_pinout_config, platform_read_I2C, platform_write_I2C);
        }
        case(LSM6DSO_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DSO_Proxy>();
            return lsm6ds_sensor->init(lsm6ds_settings, I2C_pinout_config, platform_read_I2C, platform_write_I2C);   
        }
        default: {
            return LSM6DS_ERROR_WHO_AM_I;
        }
    }
}

int8_t LSM6DS_Interface::init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_config SPI_pinout_config) {
    int32_t rst;
    int8_t whoamI;
    rst =  platform_read_SPI(SPI_pinout_config.sensor_bus, WHO_AM_I_ID, (uint8_t*)&whoamI, sizeof(int8_t));
    
    if (rst != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    switch (whoamI) {
        case(LSM6DS3_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DS3_Proxy>();
            return lsm6ds_sensor->init(lsm6ds_settings, SPI_pinout_config, platform_read_SPI, platform_write_SPI);
        }
        case(LSM6DS3TRC_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DS3TRC_Proxy>();
            return lsm6ds_sensor->init(lsm6ds_settings, SPI_pinout_config, platform_read_SPI, platform_write_SPI);
        }
        case(LSM6DSO_ID): {
            lsm6ds_sensor = std::make_unique<LSM6DSO_Proxy>();
            return lsm6ds_sensor->init(lsm6ds_settings, SPI_pinout_config, platform_read_SPI, platform_write_SPI);   
        }
        default: {
            return LSM6DS_ERROR_WHO_AM_I;
        }
    }
}

void LSM6DS_Interface::update_data() {
    lsm6ds_sensor->update_data();
}

void LSM6DS_Interface::update_data_ready_interrupt() {
    lsm6ds_sensor->update_data_ready_interrupt();
}

void LSM6DS_Interface::update_data_fifo_full_interrupt() {
    lsm6ds_sensor->update_data_fifo_full_interrupt();
}

void LSM6DS_Interface::reset_fifo() {
    lsm6ds_sensor->reset_fifo();
}

float LSM6DS_Interface::get_acc_data_mg() {
    return lsm6ds_sensor->get_acc_data_mg();
}

float LSM6DS_Interface::get_gyro_data_mdps() {
    return lsm6ds_sensor->get_gyro_data_mdps();
}

