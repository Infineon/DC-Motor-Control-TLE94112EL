/**
 * @file        spic-psoc6hal.cpp
 * @brief       TLE94112 SPI PSoC6 HAL PAL
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "../../../config/tle94112-conf.hpp"

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_PSOC6)

#include "spic-psoc6hal.hpp"

/**
 * @brief Construct a new SPICPsoc6hal::SPICPsoc6hal object
 * 
 * This function allows to set all parameters of the SPI master.
 * 
 * @param csPin    Number of the desired ChipSelect pin
 * @param misoPin  Number of the desired MISO pin
 * @param mosiPin  Number of the desired MOSI pin
 * @param sckPin   Number of the desired SystemClock pin
 * 
 * @attention This does not set the platform_spi_peripherals structure yet
 */
SPICPsoc6hal::SPICPsoc6hal(cyhal_gpio_t csPin, cyhal_gpio_t misoPin, cyhal_gpio_t mosiPin, cyhal_gpio_t sckPin)
{
	this->csPin   = csPin;
	this->misoPin = misoPin;
	this->mosiPin = mosiPin;
	this->sckPin  = sckPin;
}

/**
 * @brief Destructor of the PSOC6 SPIC class
 *
 */
SPICPsoc6hal::~SPICPsoc6hal()
{
	deinit();
}
/**
 * @brief Initialize the SPIC
 *
 * This function is initializing the chosen spi channel
 * with the given values for lsb,clock and mode
 *
 * @return Error_t
 */
Error_t SPICPsoc6hal::init()
{
	Error_t err = OK;

	cy_rslt_t cyErr = cyhal_spi_init( &this->spi, this->mosiPin, this->misoPin, this->sckPin, this->csPin, NULL, 8, CYHAL_SPI_MODE_00_LSB, false);
	if(CY_RSLT_SUCCESS != cyErr) {
		err = INTF_ERROR;
	}

	cyErr = cyhal_spi_set_frequency( &this->spi, SPI_FREQ_HZ);
	if(CY_RSLT_SUCCESS != cyErr){
		err = INTF_ERROR;
	}

	return err;
}

/**
 * @brief Deinitialize the SPIC
 *
 * This function is deinitializing the chosen spi channel.
 *
 * @return Error_t
 */
Error_t SPICPsoc6hal::deinit()
{
	cyhal_spi_free( &this->spi );
	return OK;
}

/**
 * @brief transfers a data package via the spi bus
 * @attention __enable_irq() must be used in the main.c file otherwise the transfer function
 * will be pending for ever, as the SPI subsystem is not started
 *
 * @param send         address and/or command to send
 * @param received     received data from spi bus
 * @return             Error_t
 */
Error_t SPICPsoc6hal::transfer(uint8_t send, uint8_t &received)
{
	Error_t err = OK;

	receiveBuffer[0] = received;
	cy_rslt_t cyErr = cyhal_spi_transfer( &this->spi, &send, 1u, &received, 1u, 0x0);
	if(CY_RSLT_SUCCESS != cyErr)
		err = INTF_ERROR;

	return err;
}

/**
 * @brief transfers a data package via the spi bus
 * @attention __enable_irq() must be used in the main.c file otherwise the transfer function
 * will be pending for ever, as the SPI subsystem is not started
 *
 * @param send         address and/or command to send as 16bit
 * @param received     received data from spi bus as 16bit
 * @return             Error_t
 */
Error_t SPICPsoc6hal::transfer16(uint16_t send, uint16_t &received)
{
	Error_t err = OK;

	sendBuffer[0] = (uint8_t)((send >> 8) & 0xFF);
	sendBuffer[1] = (uint8_t)(send & 0xFF);

	cy_rslt_t cyErr = cyhal_spi_transfer( &this->spi, sendBuffer, 2, receiveBuffer, 2, 0xF);
	if(CY_RSLT_SUCCESS != cyErr)
		err = INTF_ERROR;
	received = (uint16_t)(((uint16_t)receiveBuffer[0] << 8) | (receiveBuffer[1]));

	return err;
}

#endif /** TLE94112_FRAMEWORK **/
