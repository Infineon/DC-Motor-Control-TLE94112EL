/**
 * @file        TLE94112Motor-platf-rpi.hpp
 * @brief       TLE94112Motor-platf-rpi.hpp Raspberry Pi Hardware Platforms
 * @date        September 2020
 * @version     1.0.0
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * @ref         tle94112rpi
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TLE94112MOTOR_PLATF_RPI_HPP_
#define TLE94112MOTOR_PLATF_RPI_HPP_

#include "TLE94112-platf-rpi.hpp"

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_RPI)

#include "../../../corelib/TLE94112Motor.hpp"

/**
 * @addtogroup platfRpi
 * 
 * This class provides a simple API for connecting and controlling motors.
 * Each motor is assigned to a Tle94112 which acts as output driver. Calls to
 * Tle94112Motor instances are mapped to calls to Tle94112. Therefore, this
 * class does not bring new features, it does only provide further abstraction.
 *
 * @{
 */

class Tle94112MotorRpi: virtual public Tle94112Motor
{
};
/** @} */

#endif /** TLE94112_FRAMEWORK **/
#endif /** TLE94112MOTOR_PLATF_RPI_HPP_ **/