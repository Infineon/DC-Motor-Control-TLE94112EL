/*!
 * \file        TLE94112Motor-ino.hpp
 * \name        TLE94112Motor-ino.hpp - optionally include library
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     2.0.0
 * \ref         tle94112ino
 * \brief       This file can optionally be included in projects that use an Infineon
 *              DC Motor Control Shield with TLE94112
 *              It provides a higher abstraction for controlling motors with the TLE94112
 *              acting as an output driver
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef TLE94112MOTOR_INO_HPP_
#define TLE94112MOTOR_INO_HPP_

#include "config/tle94112-conf.hpp"

/**
 * @addtogroup inoApi
 * @{
 */

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_ARDUINO)


#include "TLE94112-ino.hpp"
#include "framework/arduino/wrapper/TLE94112Motor-platf-ino.hpp"

/**
 * @class Tle94112MotorIno
 *
 * @brief represents a motor connected to a TLE94112
 *
 * This class provides a simple API for connecting and controlling motors.
 * Each motor is assigned to a Tle94112 which acts as output driver. Calls to
 * Tle94112Motor instances are mapped to calls to Tle94112. Therefore, this
 * class does not bring new features, it does only provide further abstraction.
 *
 * @see Tle94112
 */
class Tle94112MotorIno: public Tle94112Motor
{
};

/**
 * @}
 */

#endif /** TLE94112_FRAMEWORK **/
#endif /** TLE94112MOTOR_INO_HPP_ **/
