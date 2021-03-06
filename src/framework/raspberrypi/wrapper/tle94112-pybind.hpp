/**
 * @file        tle94112-pybind.hpp
 * @brief       TLE94112 Raspberry Pi Python Wrapper API
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TLE94112_PYBIND_HPP_
#define TLE94112_PYBIND_HPP_

#include "../../../config/tle94112-conf.hpp"

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_RPI)

#include "../../../corelib/tle94112.hpp"
#include "../../../corelib/tle94112-motor.hpp"
#include "tle94112-rpi.hpp"

#endif /** TLE94112_FRAMEWORK **/
#endif /** TLE94112_PYBIND_HPP_ **/