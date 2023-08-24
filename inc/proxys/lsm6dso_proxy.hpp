/**
 * @file lsm6dso.hpp
 *
 * @brief This file is a declaration of the LSM6DS3 class
 *
 * @author Bruno Machado <bruno.auler@thunderatz.org>
 * @author Pedro Machado <pedro.almeida@thunderatz.org>
 *
 * @date 08/2023
 */

#ifndef __LSM6DSO_PROXY_HPP__
#define __LSM6DSO_PROXY_HPP__

#include "lsm6ds_proxy.hpp"
#include "lsm6dso_reg.h"

class LSM6DSO_Proxy : public LSM6DS_Proxy {
    public:
        /**
         * @brief Construct a new LSM6DS3_Proxy object
         * 
         */
        LSM6DSO_Proxy() = default;

        /**
         * @brief Destroy the LSM6DS3_Proxy object
         * 
         */
        ~LSM6DSO_Proxy() = default;

    private:
        stmdev_ctx_t dev_ctx;

};

#endif // __LSM6DSO_PROXY_HPP__