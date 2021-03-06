/**
 * @file        gpio-psoc6hal.hpp
 * @brief       TLE94112 GPIO PSoC6 HAL PAL
 * @copyright   Copyright (c) 2019-2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef GPIO_PSOC6HAL_HPP_
#define GPIO_PSOC6HAL_HPP_

#include "../../../config/tle94112-conf.hpp"

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_PSOC6)

#include <stdint.h>
#include "cyhal_system.h"
#include "cyhal_gpio.h"
#include "../../../pal/gpio.hpp"

using namespace tle94112;

/**
 * @addtogroup psoc6Pal
 * @{
 */

/**
 * @brief psoc6 gpio wrapper class
 * 
 */
class GPIOPsoc6hal : virtual public GPIOC
{
	private:
		cyhal_gpio_t                pin;                                 /**< Pin number */
		cyhal_gpio_direction_t      dir;                                 /**< Pin direction */
		cyhal_gpio_drive_mode_t     driveMode;                           /**< Pin drive mode */
		VLogic_t                    logic;                               /**< Pin logic */

	public:
		static const cyhal_gpio_t   unusedPin = CYHAL_NC_PIN_VALUE;      /**< Unused pin */

					GPIOPsoc6hal(cyhal_gpio_t              pin,
								 cyhal_gpio_direction_t    dir,
								 cyhal_gpio_drive_mode_t   driveMode,
								 VLogic_t                  logic);
					~GPIOPsoc6hal();
		Error_t     init();
		Error_t     deinit();
		VLevel_t    read();
		Error_t     write(VLevel_t level);
		Error_t     enable();
		Error_t     disable();
};

/** @} */

#endif /** TLE94112_FRAMEWORK **/
#endif /** GPIO_PSOC6HAL_HPP_ **/
