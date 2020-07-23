/**
 * @file        SPIC-arduino.hpp
 * @brief       Arduino PAL for the SPI cover
 * @date        June 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "spic-wiced.hpp"

#if (TLE94112_FRAMEWORK == TLE94112_FRMWK_WICED)
#include "wiced_rtos.h"
#include <wiced.h>
#include <platform.h>

/**
 * @brief Constructor of the WICED SPIC class
 *
 * This function is setting the basics for a SPIC and the default
 * spi on Arduino which is implemented as WICED_SPI_0 by patching the following:
 *
 * - <WICED_SDK>/platforms/<platform_name>/platform.h
 *   add WICED_SPI_0, to the wiced_spi_t
 * - <WICED_SDK>/platforms/<platform_name>/platform.c
 *   add the following to the platform_spi_peripherals
 *   [WICED_SPI_0]  =
 *      {
 *          .port                    = BCM4390X_SPI_0,
 *          .pin_mosi                = &platform_gpio_pins[WICED_GPIO_6],
 *          .pin_miso                = &platform_gpio_pins[WICED_GPIO_8],
 *          .pin_clock               = &platform_gpio_pins[WICED_GPIO_5],
 *          .pin_cs                  = &platform_gpio_pins[WICED_GPIO_7],
 *          .driver                  = &spi_bb_driver,
 *      },
 *    which sets the Arduino header GPIOs and the bit banging driver.
 *
 */
SPICWiced::SPICWiced() : csPin(WICED_GPIO_22), port(WICED_SPI_0)
{
	this->spi.port = port;
	this->spi.chip_select = csPin;
	this->spi.speed = 1000000;
	this->spi.mode = (SPI_CLOCK_RISING_EDGE | SPI_CLOCK_IDLE_LOW | SPI_NO_DMA | SPI_LSB_FIRST | SPI_CS_ACTIVE_LOW);
	this->spi.bits = 8;
}

/**
 * @brief Construct a new SPICWiced::SPICWiced object
 *
 * This function is setting the basics for a SPIC. It allows to set the
 * SPI channel and the used GPIOs if they are different from the standard GPIOs.
 *
 * @param[in] port     SPI channel to be used
 * @param[in] csPin    Number of the desired ChipSelect pin
 * @param[in] misoPin  Number of the desired MISO pin
 * @param[in] mosiPin  Number of the desired MOSI pin
 * @param[in] sckPin   Number of the desired SystemClock pin
 */
SPICWiced::SPICWiced(wiced_spi_t port, wiced_gpio_t csPin, wiced_gpio_t misoPin, wiced_gpio_t mosiPin, wiced_gpio_t sckPin):csPin(csPin), port(port)
{
	this->spi.port = port;
	this->spi.chip_select = csPin;
	this->spi.speed = 1000000;
	this->spi.mode = (SPI_CLOCK_RISING_EDGE | SPI_CLOCK_IDLE_HIGH | SPI_NO_DMA |SPI_LSB_FIRST | SPI_CS_ACTIVE_LOW );
	this->spi.bits = 8;

	this->spiSetting = true;
}

/**
 * @brief Destructor of the WICED SPIC class
 *
 */
SPICWiced::~SPICWiced()
{
	deinit();
}
/**
 * @brief Initialize the SPIC
 *
 * This function is initializing the chosen spi channel
 * with the given values for lsb,clock and mode
 *
 * @return      SPICWiced::Error_t
 */
SPICWiced::Error_t SPICWiced::init()
{
	this->segment.tx_buffer = sendBuffer;
	this->segment.rx_buffer = receiveBuffer;
	this->segment.length = 1;

	wiced_spi_init( &this->spi );
	return OK;
}

/**
 * @brief Deinitialize the SPIC
 *
 * This function is deinitializing the chosen spi channel.
 *
 * @return      SPICWiced::Error_t
 */
SPICWiced::Error_t SPICWiced::deinit()
{
	wiced_spi_deinit( &this->spi );
	return OK;
}

/**
 * @brief transfers a data package via the spi bus
 *
 * @param send         address and/or command to send
 * @param received     received data from spi bus
 * @return             SPICWiced::Error_t
 */
SPICWiced::Error_t SPICWiced::transfer(uint8_t send, uint8_t &received)
{
	sendBuffer[0] = send;
	receiveBuffer[0] = received;
	wiced_spi_transfer( &this->spi, &this->segment, 1);
	return OK;
}

#endif /** TLE94112_FRAMEWORK **/
