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

#ifndef __LSM6DS3TRC_HPP__
#define __LSM6DS3TRC_HPP__

#include "lsm6ds.hpp"
#include "lsm6ds3tr-c_reg.h"

class LSM6DS3TRC : public LSM6DS {
    public:
        /**
         * @brief Construct a new LSM6DS3TRC object
         * 
         */
        LSM6DS3TRC() = default;

        /**
         * @brief Destroy the LSM6DS3TRC object
         * 
         */
        ~LSM6DS3TRC() = default;

    private:
        axis3bit16_t data_raw_acceleration;
        axis3bit16_t data_raw_angular_rate;
        float acceleration_mg[3];
        float angular_rate_mdps[3];
        stmdev_ctx_t dev_ctx;
};

#endif // __LSM6DS3TRC_HPP__