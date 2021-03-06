/**
 * @file        timer-psoc6hal.cpp
 * @brief       TLE94112 Timer PSoC6 HAL PAL
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "../../../config/tle94112-conf.hpp"

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_PSOC6)

#include "timer-psoc6hal.hpp"

/**
 * @brief Constructor of the PSOC6 Timer class
 *
 */
TimerPsoc6hal::TimerPsoc6hal()
{
}

/**
 * @brief Destructor of the PSOC6 Timer class
 *
 */
TimerPsoc6hal::~TimerPsoc6hal()
{
}

/**
 * @brief Initialization of the Timer
 *
 * This function is initializing the Timer and sets
 * the elapsed time to zero.
 *
 * @return      Error_t
 */
Error_t TimerPsoc6hal::init()
{
	Error_t err = OK;

	cy_rslt_t cyErr = cyhal_timer_init(&timerHandle, NC, NULL);
	if(CY_RSLT_SUCCESS != cyErr)
		err = INTF_ERROR;

	return err;
}

/**
 * @brief Deinitialize the Timer
 *
 * This function deinitialize the Timer and also
 * resets the elapsed time variable.
 *
 * @return      Error_t
 */
Error_t TimerPsoc6hal::deinit()
{
	cyhal_timer_free(&timerHandle);
	return OK;
}

/**
 * @brief Start the timer
 *
 * This function is starting the timer.
 *
 * @return      Error_t
 */
Error_t TimerPsoc6hal::start()
{
	Error_t err = OK;

	timerConf.compare_value = 0;
	timerConf.period        = 0xFFFFFFFFUL;
	timerConf.direction     = CYHAL_TIMER_DIR_UP;
	timerConf.is_compare 	= false;
	timerConf.is_continuous = false;
	timerConf.value         = 0;

	do
	{
		cy_rslt_t cyErr = cyhal_timer_configure(&timerHandle, &timerConf);
		if(CY_RSLT_SUCCESS != cyErr)
		{
			err = INTF_ERROR;
			break;
		}

		cyErr = cyhal_timer_set_frequency(&timerHandle, 1000000);
		if(CY_RSLT_SUCCESS != cyErr)
		{
			err = INTF_ERROR;
			break;
		}

		cyErr = cyhal_timer_start(&timerHandle);
		if(CY_RSLT_SUCCESS != cyErr)
			err = INTF_ERROR;

	} while (0);

	return err;
}

/**
 * @brief Calculate the elapsed time
 *
 * This function is calculating the elapsed time since the
 * start of the timer. The value stored in the given variable
 * is in milliseconds.
 *
 * @param[in]   &elapsed                Address of a value where the elapsed time should be stored
 * @return      Error_t
 */
Error_t TimerPsoc6hal::elapsed(uint32_t &elapsed)
{
	elapsed = (uint32_t)(cyhal_timer_read(&timerHandle)/1000);
	return OK;
}

/**
 * @brief Stop the timer
 *
 * This function stops the timer and resets the
 * start time variable.
 *
 * @return      Error_t
 */
Error_t TimerPsoc6hal::stop()
{
	Error_t err = OK;

	cy_rslt_t cyErr = cyhal_timer_stop(&timerHandle);
	if(CY_RSLT_SUCCESS != cyErr)
		err = INTF_ERROR;

	return err;
}

/**
 * @brief Time delay
 *
 * This function is causing a desired delay of the application.
 * The input value is given in milliseconds.
 *
 * @param[in]   timeout                 Desired timeout in ms
 * @return      Error_t
 */
Error_t TimerPsoc6hal::delayMilli(uint32_t timeout)
{
	Error_t err = OK;

	cy_rslt_t cyErr = cyhal_system_delay_ms(timeout);
	if(CY_RSLT_SUCCESS != cyErr)
		err = INTF_ERROR;

	return err;
	return OK;
}

/**
 * @brief Time delay
 *
 * This function is causing a desired delay of the application.
 * The input value is given in microseconds.
 *
 * @param[in]   timeout                 Desired timeout in us
 * @return      Error_t
 */
Error_t TimerPsoc6hal::delayMicro(uint32_t timeout)
{
	Error_t err = OK;

	cy_rslt_t cyErr = cyhal_system_delay_ms(timeout*1000);
	if(CY_RSLT_SUCCESS != cyErr)
		err = INTF_ERROR;

	return err;
}

#endif /** TLE94112_FRAMEWORK **/
