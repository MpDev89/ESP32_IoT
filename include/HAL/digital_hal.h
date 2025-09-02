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
 * @file digital_hal.h
 * @brief this file contain the functions prototype to create an abstract interface 
 * to manage digital pins
 *
 * The following functions will be implemented:
 * - digital_init() to initialize the digital array
 * - digital_set_pin() to set pin value for a specific channel
 * - digital_set_direction() to set digital pin direction
 * - digital_set_value() to set digital output value
 * - digital_read() to read digital value
 * - digital_print() to print status of digital channel
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */
#ifndef __DIGITAL_HAL_H__
#define __DIGITAL_HAL_H__

#include "common.h"

#define NUM_DIG_PERIP 2 // number of digital peripherals

typedef struct
{
	uint8_t			pin;
	bool 			status;
  bool 			direction; // true if output, false if input
  bool 			value; // true if enabled, false if disabled
}Dig_t;

/**
 * @brief Initialize Digital Array
 *
 * Initialize the digital array with a given size and set default values.
 *
 * @param d 8-bit struct pointer to an n-element data array
 * @param size 8-bit value that indicate number of digital array 
 *
 * @return void
 */
void digital_init(Dig_t* d, uint8_t size);

/**
 * @brief Set pin value for a specific channel
 *
 * set pin value for a specific channel in the digital array.
 *
 * @param d 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of digital array 
 * @param pin 8-bit value that indicate pin number used for peripheral 
 * @param size 8-bit value that indicate number of digital array 
 *
 * @return void
 */
void digital_set_pin(Dig_t* d, uint8_t channel, uint8_t pin, uint8_t size);

/**
 * @brief Set digital pin direction
 *
 * set digital pin direction for a specific channel in the digital array.
 *
 * @param d 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of digital array 
 * @param direction bool value that indicate direction of digital function (true for output, false for input)
 * @param size 8-bit value that indicate number of digital array 
 *
 * @return void
 */
void digital_set_direction(Dig_t* d, uint8_t channel, bool direction, uint8_t size); 

/**
 * @brief Set digital output value
 *
 * set digital output value for a specific channel in the digital array.
 *
 * @param d 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of digital array 
 * @param value bool value that indicate digital output value (true for HIGH, false for LOW)
 * @param size 8-bit value that indicate number of digital array 
 *
 * @return void
 */
void digital_set_value(Dig_t* d, uint8_t channel, bool value, uint8_t size); 

/**
 * @brief Read digital value
 *
 * read digital value for a specific channel in the digital array.
 *
 * @param d 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of digital array 
 * @param size 8-bit value that indicate number of digital array 
 *
 * @return int value of the digital channel (HIGH or LOW), or -1 if the channel is not valid
 */
int digital_read(Dig_t* d, uint8_t channel, uint8_t size);

/**
 * @brief Print status of digital channel
 *
 * Print status of digital channel to the serial monitor.
 *
 * @param d 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of digital array 
 *
 * @return void
 */
void digital_print(Dig_t* d, uint8_t channel); 


#endif /* __DIGITAL_HAL_H__ */










