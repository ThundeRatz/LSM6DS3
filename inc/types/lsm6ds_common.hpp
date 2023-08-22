/**
 * @file lsm6ds_common_type.h
 *
 * @brief IMU common types.
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 *
 * @date 08/2023
 */

#ifndef LSM6DS_COMMON_H
#define LSM6DS_COMMON_H

#include <iostream>

/* Error codes */
typedef int8_t LSM6DS_error;
#define LSM6DS_ERROR_NONE ((LSM6DS_error) 0)
#define LSM6DS_ERROR_WHO_AM_I ((LSM6DS_error) 1)
#define LSM6DS_ERROR_WRITE_REGISTER ((LSM6DS_error) 2)

typedef union {
    int16_t i16bit[3];
    uint8_t u8bit[6];
} axis3bit16_t;

typedef union {
    int16_t i16bit;
    uint8_t u8bit[2];
} axis1bit16_t;

#endif // LSM6DS_COMMON_H