/******************************************************************************
 *
 * Copyright (c) 2025 Marconatale Parise. All rights reserved.
 *
 * This file is part of proprietary software. Unauthorized copying, distribution,
 * or modification of this file, via any medium, is strictly prohibited without
 * prior written permission from the copyright holder.
 *
 *****************************************************************************/
/**
 * @file peripheral.h
 * @brief this file contain the functions prototype to link the peripher to functionalities
 *
 * The following functions will be implemented:
 * - peripheral_init() to initialize the peripherals
 * - turn_led() to control the LED state
 * - get_temperature() to read the temperature from the BMP280 sensor
 * - read_solar_radiation() to read the solar radiation status
 * - read_humidity() to read the humidity pertentage from the analog sensor
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */

#ifndef __PERIPHERAL_H__
#define __PERIPHERAL_H__

#include "common.h"
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

// defined the pins for peripherals
#define DIODE_LED_1_pin 4
#define SOLAR_SNS_1_pin 5
#define HUMIDITY_1_pin 32

// defined the channels for peripherals
#define DIODE_LED_1_ch  0
#define SOLAR_SNS_1_ch  1
#define HUMIDITY_1_ch  0

/**
 * @brief Initialize peripherals
 *
 * Initialize peripherals to asserve the functionalities of the system. 
 *
 * NO parameters are required for this function.
 *
 * @return void
 */
void peripheral_init();

/**
 * @brief Turn LED on or off
 *
 * Set the state of the LED for a specific digital channel.
 *
 * @param channel 8-bit value that indicate channel of digital array
 * @param value boolean value to set the LED state (true for ON, false for OFF)
 *
 * @return void
 */
void turn_led(uint8_t channel, bool value);

/**
 * @brief Get temperature from BMP280 sensor
 *
 * Read the temperature from the BMP280 sensor and return the value.
 *
 * NO parameters are required for this function.
 *
 * @return float Temperature in degrees Celsius
 */
float get_temperature();

/**
 * @brief Read solar radiation status
 *
 * Read the status of the solar radiation sensor for a specific digital channel.
 *
 * @param channel 8-bit value that indicate channel of digital array
 *
 * @return int Status of the solar radiation sensor (0 or 1)
 */
int read_solar_radiation(uint8_t channel);

/**
 * @brief Read humidity percentage
 *
 * Read the humidity percentage from the analog sensor for a specific analog channel.
 *
 * @param channel 8-bit value that indicate channel of analog array
 *
 * @return float Humidity percentage
 */
float read_humidity(uint8_t channel);

#endif /* __PERIPHERAL_H__ */