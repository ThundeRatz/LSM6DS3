/**
 * @file lsm6ds_c_interface.cpp
 *
 * @brief This file is a declaration for a c compatible interface
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */

#include "lsm6ds_c_interface.h"
#include "lsm6ds_interface.hpp"

extern "C" {

static LSM6DS_Interface sensor_interface;

int8_t init_I2C(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_pinout I2C_pinout_config) {
    return sensor_interface.init(lsm6ds_settings, I2C_pinout_config);
}

int8_t init_SPI(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_pinout SPI_pinout_config) {
    return sensor_interface.init(lsm6ds_settings, SPI_pinout_config);
}

void update_data() {
    return sensor_interface.update_data();
}


void LSM6DS_Interface::update_data_ready_interrupt() {
    sensor_interface.update_data_ready_interrupt();
}

void LSM6DS_Interface::update_data_fifo_full_interrupt() {
    sensor_interface.update_data_fifo_full_interrupt();
}

void LSM6DS_Interface::reset_fifo() {
    sensor_interface.reset_fifo();
}

float* LSM6DS_Interface::get_acc_data_mg() {
    return sensor_interface.get_acc_data_mg();
}

float* LSM6DS_Interface::get_gyro_data_mdps() {
    return sensor_interface.get_gyro_data_mdps();
}

}
