/*!
 * \name        control2Motors
 * \author      Infineon Technologies AG
 * \copyright   2019 Infineon Technologies AG
 * \brief       This example demonstrates how to control two motors, their speed and direction with the TLE94112 shield.
 *
 * \details
 * By attaching a Tle94112 controller object to two Tle94112Motor objects, we can generate
 * an easy to handle motor object for each motor. We can easily attach this motor object
 * two any of the halfbridges and to any of the PWM units. This is done in the setup part.
 * Keep in mind that you have to initialize the Tle94112 controller and each motor object,
 * which is done in the setup function.
 * After that we can take the motor start, stop and setSpeed function to easily control
 * each motor.
 *
 * \attention Motors have depending on their size a very big latency until a motor has
 * fully started or is stopped to 0. Specially the time between a start and stop and vice versa
 * is much higher than the processing speed of any microcontroller. This is solved in this example
 * with the delay command, but there are better solutions than that.
 * These delays are needed because a direct switch between start and stop will lead to high currents
 * and the TLE94112 will signal an overcurrent.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef CONTROL2MOTORS_HPP_
#define CONTROL2MOTORS_HPP_

#include "../../../../config/tle94112-conf.hpp"

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_WICED)

#include <stdlib.h>
#include <wiced.h>
#include <tle94112-platf-wiced.hpp>
#include <tle94112-wiced.hpp>
#include <tle94112-motor.hpp>
#include "wiced_rtos.h"

extern "C" void application_start();

#endif /** TLE94112_FRAMEWORK **/
#endif /* CONTROL2MOTORS_HPP_ */
