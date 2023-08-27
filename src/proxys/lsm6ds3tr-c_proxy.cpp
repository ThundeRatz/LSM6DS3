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
#include <cstring>

/*****************************************
 * Class Public Methods Bodies Definitions
 *****************************************/

int8_t LSM6DS3TRC_Proxy::init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_I2C_pinout_t I2C_pinout_config, platform_read_f platform_read, platform_write_f platform_write) {
    int32_t error_code;
    sensor_settings = lsm6ds_settings;
    pinout_config.I2C_pinout = I2C_pinout_config;
    dev_ctx.handle = (lsm6ds_config_t*) &pinout_config.I2C_pinout;
    dev_ctx.read_reg = platform_read;
    dev_ctx.write_reg = platform_write;
    pinout_config.I2C_pinout.I2C_init();

    error_code = base_init();

    if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    if (sensor_settings.lsm6ds_fifo_md == LSM6DS_FIFO_MODE) {
        error_code = fifo_mode_init();
        if (error_code != 0) {
            return LSM6DS_ERROR_WRITE_REGISTER;
        }
    }

    if (sensor_settings.lsm6ds_gy_interrupt != LSM6DS_GY_DRDY_NONE || sensor_settings.lsm6ds_xl_interrupt != LSM6DS_XL_DRDY_NONE) {
        error_code = fifo_mode_init();
        if (error_code != 0) {
            return LSM6DS_ERROR_WRITE_REGISTER;
        }
    }

    return LSM6DS_ERROR_NONE;
}


int8_t LSM6DS3TRC_Proxy::init(lsm6ds_settings_t lsm6ds_settings, lsm6ds_SPI_pinout_t SPI_pinout_config, platform_read_f platform_read, platform_write_f platform_write) {
    int32_t error_code;
    sensor_settings = lsm6ds_settings;
    pinout_config.SPI_pinout = SPI_pinout_config;
    dev_ctx.handle = (lsm6ds_config_t*) &pinout_config.I2C_pinout;
    dev_ctx.read_reg = platform_read;
    dev_ctx.write_reg = platform_write;
    pinout_config.I2C_pinout.I2C_init();

    error_code = base_init();

    if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    if (sensor_settings.lsm6ds_fifo_md == LSM6DS_FIFO_MODE) {
        error_code = fifo_mode_init();
        if (error_code != 0) {
            return LSM6DS_ERROR_WRITE_REGISTER;
        }
    }

    if (sensor_settings.lsm6ds_gy_interrupt != LSM6DS_GY_DRDY_NONE || sensor_settings.lsm6ds_xl_interrupt != LSM6DS_XL_DRDY_NONE) {
        error_code = fifo_mode_init();
        if (error_code != 0) {
            return LSM6DS_ERROR_WRITE_REGISTER;
        }
    }

    return LSM6DS_ERROR_NONE;
}


void LSM6DS3TRC_Proxy::update_data() {
    uint8_t reg;

    /* Read output only if new value is available */
    lsm6ds3tr_c_xl_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
        /* Read acceleration field data */
        memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
        lsm6ds3tr_c_acceleration_raw_get(&dev_ctx, data_raw_acceleration.i16bit);

        for (int i = 0; i < 3; i++) {
            acceleration_mg[i] = acc_conversion_f(data_raw_acceleration.i16bit[i]);
        }
    }

    lsm6ds3tr_c_gy_flag_data_ready_get(&dev_ctx, &reg);

    if (reg) {
        /* Read angular rate field data */
        memset(data_raw_angular_rate.u8bit, 0x00, 3 * sizeof(int16_t));
        lsm6ds3tr_c_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate.i16bit);

        for (int j = 0; j < 3; j++) {
            angular_rate_mdps[j] = gyro_conversion_f(data_raw_angular_rate.i16bit[j]);
        }
    }
}

void LSM6DS3TRC_Proxy::update_data_ready_interrupt() {
    /* Read acceleration field data when corresponding INT is HIGH */
    if (HAL_GPIO_ReadPin(int_gpio_port_xl, int_gpio_pin_xl) == 1) {
        memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
        lsm6ds3tr_c_acceleration_raw_get(&dev_ctx, data_raw_acceleration.i16bit);

        for (int i = 0; i < 3; i++) {
            acceleration_mg[i] = acc_conversion_f(data_raw_acceleration.i16bit[i]);
        }
    }

    /* Read angular rate field data when corresponding INT is HIGH */
    if (HAL_GPIO_ReadPin(int_gpio_port_g, int_gpio_pin_g) == 1) {
        memset(data_raw_angular_rate.u8bit, 0x00, 3 * sizeof(int16_t));
        lsm6ds3tr_c_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate.i16bit);

        for (int i = 0; i < 3; i++) {
            angular_rate_mdps[i] = gyro_conversion_f(data_raw_angular_rate.i16bit[i]);
        }
    }
}

void LSM6DS3TRC_Proxy::update_data_fifo_full_interrupt() {
    uint16_t fifo_size;
    lsm6ds3tr_c_fifo_data_level_get(&dev_ctx, &fifo_size);
    float data_sum[3] = {0};
    uint8_t current_axis;
    for (uint8_t i = 0; i < fifo_size; i++) {
        current_axis = i % 3;
        if (sensor_settings.lsm6ds_dec_fifo_gyro != LSM6DS_FIFO_GY_DISABLE) {
            memset(data_raw_angular_rate.u8bit, 0x00, 3 * sizeof(int16_t));
            lsm6ds3tr_c_fifo_raw_data_get(&dev_ctx, data_raw_angular_rate.u8bit + 2 * current_axis);
            data_sum[current_axis] += gyro_conversion_f(data_raw_angular_rate.i16bit[current_axis]);
        }
        if (sensor_settings.lsm6ds_dec_fifo_xl != LSM6DS_FIFO_XL_DISABLE ) {
            memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
            lsm6ds3tr_c_fifo_raw_data_get(&dev_ctx, data_raw_acceleration.u8bit + 2 * current_axis);
            data_sum[current_axis] += acc_conversion_f(data_raw_acceleration.i16bit[current_axis]);
        }
    }
    for (uint8_t i = 0; i < 3; i++) {
        if (sensor_settings.lsm6ds_dec_fifo_gyro != LSM6DS_FIFO_GY_DISABLE) {
            angular_rate_mdps[i] = data_sum[i]/(fifo_size/3);
        }
        if (sensor_settings.lsm6ds_dec_fifo_xl != LSM6DS_FIFO_XL_DISABLE) {
            acceleration_mg[i] = data_sum[i]/(fifo_size/3);
        }
    }
    lsm6ds3tr_c_fifo_mode_set(&dev_ctx, LSM6DS3TR_C_BYPASS_MODE);
    lsm6ds3tr_c_fifo_mode_set(&dev_ctx, LSM6DS3TR_C_FIFO_MODE);
}

void LSM6DS3TRC_Proxy::reset_fifo() {
    lsm6ds3tr_c_fifo_mode_set(&dev_ctx, LSM6DS3TR_C_BYPASS_MODE);
    lsm6ds3tr_c_fifo_mode_set(&dev_ctx, LSM6DS3TR_C_FIFO_MODE);
}

float* LSM6DS3TRC_Proxy::get_acc_data_mg() {
    return acceleration_mg;
}

float* LSM6DS3TRC_Proxy::get_gyro_data_mdps() {
    return angular_rate_mdps;
}

/*****************************************
 * Class Private Methods Bodies Definitions
 *****************************************/

int8_t LSM6DS3TRC_Proxy::base_init() {
    uint8_t rst;
    int32_t error_code;
    /* Restore default configuration */
    lsm6ds3tr_c_reset_set(&dev_ctx, PROPERTY_ENABLE);

    do {
        lsm6ds3tr_c_reset_get(&dev_ctx, &rst);
    } while (rst);

    /* Enable Block Data Update */
    error_code = lsm6ds3tr_c_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

    if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    /* Register address automatically incremented during a multiple byte access with a serial interface */
    error_code = lsm6ds3tr_c_auto_increment_set(&dev_ctx, PROPERTY_ENABLE);

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    /* Set full scale */
    error_code = lsm6ds3tr_c_xl_full_scale_set(&dev_ctx, (lsm6ds3tr_c_fs_xl_t) sensor_settings.lsm6ds_xl_fs);

    if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    error_code = lsm6ds3tr_c_gy_full_scale_set(&dev_ctx, (lsm6ds3tr_c_fs_g_t) sensor_settings.lsm6ds_fs_g);

    if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    /* Select the function to convert acc raw data to mg */
    switch (sensor_settings.lsm6ds_xl_fs) {
        case 0:
            acc_conversion_f = lsm6ds3tr_c_from_fs2g_to_mg;
            break;

        case 1:
            acc_conversion_f = lsm6ds3tr_c_from_fs16g_to_mg;
            break;

        case 2:
            acc_conversion_f = lsm6ds3tr_c_from_fs4g_to_mg;
            break;

        case 3:
            acc_conversion_f = lsm6ds3tr_c_from_fs8g_to_mg;
            break;

        default:
            acc_conversion_f = lsm6ds3tr_c_from_fs2g_to_mg;
            break;
    }

    /* Select the function to convert gyro raw data to mdps */
    switch (sensor_settings.lsm6ds_fs_g) {
        case 0:
            gyro_conversion_f = lsm6ds3tr_c_from_fs250dps_to_mdps;
            break;

        case 1:
            gyro_conversion_f = lsm6ds3tr_c_from_fs125dps_to_mdps;
            break;

        case 2:
            gyro_conversion_f = lsm6ds3tr_c_from_fs500dps_to_mdps;
            break;

        case 4:
            gyro_conversion_f = lsm6ds3tr_c_from_fs1000dps_to_mdps;
            break;

        case 6:
            gyro_conversion_f = lsm6ds3tr_c_from_fs2000dps_to_mdps;
            break;

        default:
            gyro_conversion_f = lsm6ds3tr_c_from_fs250dps_to_mdps;
            break;
    }

    /* Set Output Data Rate for Acc and Gyro */
    error_code = lsm6ds3tr_c_xl_data_rate_set(&dev_ctx, (lsm6ds3tr_c_odr_xl_t) sensor_settings.lsm6ds_odr_xl);

    if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    error_code = lsm6ds3tr_c_gy_data_rate_set(&dev_ctx, (lsm6ds3tr_c_odr_g_t) sensor_settings.lsm6ds_odr_g);

    if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    return LSM6DS_ERROR_NONE;
}

int8_t LSM6DS3TRC_Proxy::interrupt_init() {
    int32_t error_code;
     /* Enable interrupt generation on DRDY INT1 and INT2 pin */
    lsm6ds3tr_c_pin_int1_route_get(&dev_ctx, &int_1_reg);
    lsm6ds3tr_c_pin_int2_route_get(&dev_ctx, &int_2_reg);

    switch(sensor_settings.lsm6ds_xl_interrupt) {
        case(LSM6DS_XL_DRDY_INT_1): {
            int_1_reg.int1_drdy_xl = PROPERTY_ENABLE;
            int_gpio_port_xl = pinout_config.common_pinout.int1_port;
            int_gpio_pin_xl =  pinout_config.common_pinout.int1_pin;
            break;
        }
        case(LSM6DS_XL_DRDY_INT_2): {
            int_2_reg.int2_drdy_xl = PROPERTY_ENABLE;
            int_gpio_port_xl = pinout_config.common_pinout.int2_port;
            int_gpio_pin_xl =  pinout_config.common_pinout.int2_pin;
            break;
        }
        default: {
            return LSM6DS_ERROR_INVALID_SETTING;
        }
    }

      switch(sensor_settings.lsm6ds_gy_interrupt) {
        case(LSM6DS_GY_DRDY_INT_1): {
            int_1_reg.int1_drdy_g = PROPERTY_ENABLE;
            int_gpio_port_g = pinout_config.common_pinout.int1_port;
            int_gpio_pin_g =  pinout_config.common_pinout.int1_pin;
            break;
        }
        case(LSM6DS_GY_DRDY_INT_2): {
            int_2_reg.int2_drdy_g = PROPERTY_ENABLE;
            int_gpio_port_g = pinout_config.common_pinout.int2_port;
            int_gpio_pin_g = pinout_config.common_pinout.int2_pin;
            break;
        }
        default: {
           return LSM6DS_ERROR_INVALID_SETTING;
        }
    }

    error_code = lsm6ds3tr_c_pin_int1_route_set(&dev_ctx, int_1_reg);

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    lsm6ds3tr_c_pin_int2_route_set(&dev_ctx, int_2_reg);

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    return LSM6DS_ERROR_NONE;
}

int8_t LSM6DS3TRC_Proxy::fifo_mode_init() {
    int32_t error_code;
    lsm6ds3tr_c_pin_int1_route_get(&dev_ctx, &int_1_reg);
    lsm6ds3tr_c_pin_int2_route_get(&dev_ctx, &int_2_reg);

    switch (sensor_settings.lsm6ds_fifo_interrupt) {
        case(LSM6DS_FIFO_FULL_INT_1): {
            int_1_reg.int1_full_flag = PROPERTY_ENABLE;
            error_code =  lsm6ds3tr_c_pin_int1_route_set(&dev_ctx, int_1_reg);
            break;
        }
        case(LSM6DS_FIFO_FULL_INT_2): {
            int_2_reg.int2_full_flag = PROPERTY_ENABLE;
            error_code =  lsm6ds3tr_c_pin_int2_route_set(&dev_ctx, int_2_reg);
            break;
        }
        default: {
            return LSM6DS_ERROR_INVALID_SETTING;
        }
    }

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    error_code = lsm6ds3tr_c_fifo_stop_on_wtm_set(&dev_ctx, PROPERTY_ENABLE);

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    error_code =  lsm6ds3tr_c_fifo_watermark_set(&dev_ctx, sensor_settings.lsm6ds_threshold_fifo);

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    error_code =  lsm6ds3tr_c_fifo_gy_batch_set(&dev_ctx, (lsm6ds3tr_c_dec_fifo_gyro_t) sensor_settings.lsm6ds_dec_fifo_gyro);

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    error_code =  lsm6ds3tr_c_fifo_xl_batch_set(&dev_ctx, (lsm6ds3tr_c_dec_fifo_xl_t) sensor_settings.lsm6ds_dec_fifo_xl);

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

     error_code =  lsm6ds3tr_c_fifo_data_rate_set(&dev_ctx, (lsm6ds3tr_c_odr_fifo_t) sensor_settings.lsm6ds_odr_fifo);

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    error_code =  lsm6ds3tr_c_fifo_mode_set(&dev_ctx, (lsm6ds3tr_c_fifo_mode_t) sensor_settings.lsm6ds_fifo_md);

     if (error_code != 0) {
        return LSM6DS_ERROR_WRITE_REGISTER;
    }

    return LSM6DS_ERROR_NONE;
}
