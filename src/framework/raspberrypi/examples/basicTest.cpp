  
/*!
 * \name        basicTest
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     2.0.0
 * \brief       This example runs a basic controller test with one attached motor on the TLE94112 HAT for Raspberry Pi
 * \details
 * It will run the motor in forward and backward direction if the motor
 * is able to run in both directions. Otherwise it will only run in on direction.
 * Take this example as a first test when starting with this shield.
 *
 * SPDX-License-Identifier: MIT
 *
 */

/*
 * As this library works with multiple frameworks,
 * this part is needed to avoid trying to compile
 * this example from other frameworks.
 */
#include "../../../config/tle94112-conf.hpp"
#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_RPI)

/* Infineon library for multi half bridge */
#include "tle94112-rpi.hpp"
#include "tle94112-motor.hpp"

/* 3rd party libraries for this example */
#include <cstdio>
#include <bcm2835.h>

int main(int argc, char const *argv[])
{
  
  // Tle94112 Object on Shield 1
Tle94112Rpi controller;

// Tle94112Motor Objects on controller
Tle94112Motor motor(controller);


  // Enable MotorController on all Shields and Motors
  // Note: Required to be done before starting to configure the motor
  // controller is set to default CS0 pin
  controller.begin();

  // Connect a motor to HB1/HB2 highside and HB3/HB4 lowside
  // With two combined halfbridges the motor can have up to 1.8 A
  // IMPORTANT connect PWM to Lowside as higside is active Free wheeling
  motor.initConnector(motor.HIGHSIDE, controller.TLE_NOPWM, controller.TLE_HB1, controller.TLE_NOHB, controller.TLE_NOHB, controller.TLE_NOHB);
  motor.initConnector(motor.LOWSIDE,  controller.TLE_PWM1,  controller.TLE_HB5, controller.TLE_NOHB, controller.TLE_NOHB, controller.TLE_NOHB);
  
  // start the motor controller
  motor.begin();

  printf("Init ready\n");

  // coast the motor
  motor.coast();
  delay(1000);

  // max forward/backward
  printf("max forward/backward\n");
  motor.start(255);

  delay(1000);
  motor.coast();
  delay(1000);
  motor.start(-255);
  delay(1000);
  motor.coast();
  delay(1000);

  // ramp ripple forward/backward
  printf("ramp ripple forward/backward\n");
  motor.start(255); // start max forward
  delay(1000);
  motor.rampSpeed(0, 5000); // ramp down to 0
  delay(1000);
  motor.start(-255); // start max backward
  delay(1000);
  motor.rampSpeed(0, 5000); // ramp down to 0
  delay(1000);

  // ramp up/down forward
  printf("ramp up/down forward\n");
  motor.start(50); // start above 0 to allow motor to start
  motor.rampSpeed(255, 5000); // ramp up to max
  delay(1000);
  motor.rampSpeed(100, 5000); // ramp down
  delay(1000);
  motor.rampSpeed(255, 5000); // ramp up to max
  delay(1000);
  motor.rampSpeed(0, 5000); // ramp down to 0

  // ramp up/down backward
  printf("ramp up/down backward\n");
  motor.start(50); // start above 0 to allow motor to start
  motor.rampSpeed(-255, 5000); // ramp up to min
  delay(1000);
  motor.rampSpeed(-100, 5000); // ramp up
  delay(1000);
  motor.rampSpeed(-255, 5000); // ramp up to min
  delay(1000);
  motor.rampSpeed(0, 5000); // ramp up to 0

  // ramp transient with a change in rotation direction
  printf("ramp transient\n");
  motor.rampSpeed(-255, 1000); // ramp down to min
  delay(1000);
  motor.rampSpeed(255, 1000); // ramp up to max
  delay(1000);
  motor.rampSpeed(-255, 1000); // ramp down to min
  delay(1000);
  motor.rampSpeed(0, 1000); // ramp up to 0
  delay(1000);

  // stop and coast
  printf("stop and coast\n");
  motor.stop(255); // stop and hold with max force
  delay(1000);
  motor.coast();
  delay(1000);

}

#endif /** TLE94112_FRAMEWORK **/