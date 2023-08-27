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


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

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

typedef enum {
    LSM6DS_BYPASS_MODE = 0,
    LSM6DS_FIFO_MODE = 1,
    LSM6DS_STREAM_TO_FIFO_MODE = 3,
    LSM6DS_BYPASS_TO_STREAM_MODE = 4,
    LSM6DS_STREAM_MODE = 6,
} lsm6ds_fifo_md_t;

typedef enum {
    LSM6DS_FIFO_DISABLE = 0,
    LSM6DS_FIFO_12Hz5 = 1,
    LSM6DS_FIFO_26Hz = 2,
    LSM6DS_FIFO_52Hz = 3,
    LSM6DS_FIFO_104Hz = 4,
    LSM6DS_FIFO_208Hz = 5,
    LSM6DS_FIFO_416Hz = 6,
    LSM6DS_FIFO_833Hz = 7,
    LSM6DS_FIFO_1k66Hz = 8,
    LSM6DS_FIFO_3k33Hz = 9,
    LSM6DS_FIFO_6k66Hz = 10,
} lsm6ds_odr_fifo_t;

typedef enum {
    LSM6DS_FIFO_GY_DISABLE = 0,
    LSM6DS_FIFO_GY_NO_DEC = 1,
    LSM6DS_FIFO_GY_DEC_2 = 2,
    LSM6DS_FIFO_GY_DEC_3 = 3,
    LSM6DS_FIFO_GY_DEC_4 = 4,
    LSM6DS_FIFO_GY_DEC_8 = 5,
    LSM6DS_FIFO_GY_DEC_16 = 6,
    LSM6DS_FIFO_GY_DEC_32 = 7,
} lsm6ds_dec_fifo_gyro_t;

typedef enum {
    LSM6DS_FIFO_XL_DISABLE = 0,
    LSM6DS_FIFO_XL_NO_DEC = 1,
    LSM6DS_FIFO_XL_DEC_2 = 2,
    LSM6DS_FIFO_XL_DEC_3 = 3,
    LSM6DS_FIFO_XL_DEC_4 = 4,
    LSM6DS_FIFO_XL_DEC_8 = 5,
    LSM6DS_FIFO_XL_DEC_16 = 6,
    LSM6DS_FIFO_XL_DEC_32 = 7,
} lsm6ds_dec_fifo_xl_t;

typedef enum lsm6ds_gy_interrupt {
    LSM6DS_GY_DRDY_NONE,
    LSM6DS_GY_DRDY_INT_1,
    LSM6DS_GY_DRDY_INT_2
} lsm6ds_gy_interrupt_t;

typedef enum lsm6ds_xl_interrupt {
    LSM6DS_XL_DRDY_NONE,
    LSM6DS_XL_DRDY_INT_1,
    LSM6DS_XL_DRDY_INT_2
} lsm6ds_xl_interrupt_t;

typedef enum lsm6ds_fifo_interrupt {
    LSM6DS_FIFO_FULL_NONE,
    LSM6DS_FIFO_FULL_INT_1,
    LSM6DS_FIFO_FULL_INT_2
} lsm6ds_fifo_interrupt_t;


/* Struct of acc/gyro sensitivities and data rates settings */
typedef struct lsm6ds_settings {
    lsm6ds_xl_fs_t  lsm6ds_xl_fs;
    lsm6ds_fs_g_t   lsm6ds_fs_g;
    lsm6ds_odr_xl_t lsm6ds_odr_xl;
    lsm6ds_odr_g_t  lsm6ds_odr_g;
    lsm6ds_gy_interrupt_t lsm6ds_gy_interrupt;
    lsm6ds_xl_interrupt_t lsm6ds_xl_interrupt;
    lsm6ds_fifo_md_t lsm6ds_fifo_md;
    lsm6ds_odr_fifo_t lsm6ds_odr_fifo;
    lsm6ds_dec_fifo_gyro_t lsm6ds_dec_fifo_gyro;
    lsm6ds_dec_fifo_xl_t lsm6ds_dec_fifo_xl;
    lsm6ds_fifo_interrupt_t lsm6ds_fifo_interrupt;
    uint16_t lsm6ds_threshold_fifo;
} lsm6ds_settings_t;

#ifdef __cplusplus
}
#endif

#endif // LSM6DS_SETTINGS_TYPE_H
