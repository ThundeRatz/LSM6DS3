/**
 * @file lsm6ds_settings_type.h
 *
 * @brief IMU settings types.
 *
 * @author Pedro Henrique <pedro.almeida@thunderatz.org>
 *
 * @date 07/2023
 */

#ifndef LSM6DS_SETTINGS_TYPE_H
#define LSM6DS_SETTINGS_TYPE_H

typedef enum {
    LSM6DS_2g = 0,
    LSM6DS_16g = 1,
    LSM6DS_4g = 2,
    LSM6DS_8g = 3,
} lsm6ds_xl_fs_t;

typedef enum {
    LSM6DS_250dps = 0,
    LSM6DS_125dps = 1,
    LSM6DS_500dps = 2,
    LSM6DS_1000dps = 4,
    LSM6DS_2000dps = 6,
} lsm6ds_fs_g_t;

typedef enum {
    LSM6DS_XL_ODR_OFF = 0,
    LSM6DS_XL_ODR_12Hz5 = 1,
    LSM6DS_XL_ODR_26Hz = 2,
    LSM6DS_XL_ODR_52Hz = 3,
    LSM6DS_XL_ODR_104Hz = 4,
    LSM6DS_XL_ODR_208Hz = 5,
    LSM6DS_XL_ODR_416Hz = 6,
    LSM6DS_XL_ODR_833Hz = 7,
    LSM6DS_XL_ODR_1667Hz = 8,
    LSM6DS_XL_ODR_3333Hz = 9,
    LSM6DS_XL_ODR_6667Hz = 10,
} lsm6ds_odr_xl_t;

typedef enum {
    LSM6DS_GY_ODR_OFF = 0,
    LSM6DS_GY_ODR_12Hz5 = 1,
    LSM6DS_GY_ODR_26Hz = 2,
    LSM6DS_GY_ODR_52Hz = 3,
    LSM6DS_GY_ODR_104Hz = 4,
    LSM6DS_GY_ODR_208Hz = 5,
    LSM6DS_GY_ODR_416Hz = 6,
    LSM6DS_GY_ODR_833Hz = 7,
    LSM6DS_GY_ODR_1667Hz = 8,
    LSM6DS_GY_ODR_3333Hz = 9,
    LSM6DS_GY_ODR_6667Hz = 10,
} lsm6ds_odr_g_t;

#endif // LSM6DS_SETTINGS_TYPE_H
