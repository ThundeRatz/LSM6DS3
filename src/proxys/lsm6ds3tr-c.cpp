/**
 * @file lsm6ds3.cpp
 *
 * @brief This file is a definiton of the LSM6DS3 class
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */

#include "lsm6ds3tr-c_proxy.hpp"

/*****************************************
 * Class Public Methods Bodies Definitions
 *****************************************/

int8_t LSM6DS3TRC_Proxy::init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_pinout_t I2C_pinout_config, platform_read_f platform_read, platform_write_f platform_write) {
    int32_t rst;
    pinout_config.I2C_pinout = I2C_pinout_config;
    dev_ctx.handle = pinout_config.I2C_pinout.sensor_bus;
    dev_ctx.read_reg = platform_read;
    dev_ctx.write_reg = platform_write;

    pinout_config.I2C_pinout.I2C_init();


    
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

int8_t LSM6DS3TRC_Proxy::init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_config SPI_pinout_config, platform_func_t platform_read, platform_func_t platform_write) {
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

void LSM6DS3TRC_Proxy::re3update_data() {
    lsm6ds_sensor->update_data();
}

void LSM6DS3TRC_Proxy::update_data_ready_interrupt() {
    lsm6ds_sensor->update_data_ready_interrupt();
}

void LSM6DS3TRC_Proxy::update_data_fifo_full_interrupt() {
    lsm6ds_sensor->update_data_fifo_full_interrupt();
}

void LSM6DS3TRC_Proxy::reset_fifo() {
    lsm6ds_sensor->reset_fifo();
}

float LSM6DS3TRC_Proxy::get_acc_data_mg() {
    return lsm6ds_sensor->get_acc_data_mg();
}

float LSM6DS3TRC_Proxy::get_gyro_data_mdps() {
    return lsm6ds_sensor->get_gyro_data_mdps();
}

