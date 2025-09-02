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
 * @file analog_hal.h
 * @brief this file contain the functions prototype to create an abstract layer 
 * to manage analog pins based on data structure
 *
 * The following functions will be implemented:
 * - analog_init() to initialize the analog array
 * - analog_set_pin() to set pin value for a specific channel
 * - Ff_buffer_add() to fill FIFO buffer with new data
 * - data_is_valid() to verify data validity
 * - spike_counter() to count number of spikes
 * - analog_get_media() to get media from samples collected in the FIFO buffer
 * - analog_read_data() to read data from analog pins
 * - analog_print() to print data for a specific channel
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */

#ifndef __ANALOG_HAL_H__
#define __ANALOG_HAL_H__

#include "common.h"

#define VUSB 5000
#define VBATT 4200
#define VREG 3320
#define RANGE   (4095*300)/VREG   //300mV in bit
#define NO_ADC_SPIKE  0 // no spike detected
#define LIMIT_ADC_SPIKE 3 // spike detected and data is valid

#define NUM_ANALOG_PERIP 1 // number of analog peripherals
#define BUFFER_SIZE 4 // number of samples to store in the buffer

typedef struct 
{
  uint8_t    length; // index of the data in the buffer
	uint16_t	 data_set[BUFFER_SIZE];
  uint16_t   data_media;
  uint16_t   count; 
}Fifo_buf_t;

typedef struct 
{
	uint8_t			pin;
	bool 			  status;
	Fifo_buf_t		fbuf;
  uint8_t     counter_spike;
  
}Analog_t;

/**
 * @brief Initialize analog Array
 *
 * Initialize the analog array with a given size and set default values.
 *
 * @param a 8-bit struct pointer to an n-element data array
 * @param size 8-bit value that indicate number of analog array 
 *
 * @return void
 */
void analog_init(Analog_t* a, uint8_t size);

/**
 * @brief Set pin value for a specific channel
 *
 * set pin value for a specific channel in the analog array.
 *
 * @param a 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of analog array 
 * @param pin 8-bit value that indicate pin number used for peripheral 
 * @param size 8-bit value that indicate number of analog array 
 *
 * @return void
 */
void analog_set_pin(Analog_t* a, uint8_t channel, uint8_t pin, uint8_t size);

/**
 * @brief fill fifo with new data
 *
 * Add new data to the FIFO buffer for a specific channel in the analog array.
 *
 * @param a 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of analog array 
 * @param data_read 16-bit value new data to be added to the buffer
 * @param size 8-bit value that indicate number of analog array 
 *
 * @return void
 */
void Ff_buffer_add(Analog_t* a, uint8_t channel, uint16_t data_read, uint8_t size);

/**
 * @brief verify data validity
 *
 * Check if the new data is valid based on ranges
 *
 * @param a 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of analog array 
 * @param data_read 16-bit value new data to be added to the buffer
 * @param size 8-bit value that indicate number of analog array 
 *
 * @return bool true if data is valid, false otherwise
 */
bool data_is_valid(Analog_t* a, uint8_t channel, uint16_t data_read, uint8_t size);

/**
 * @brief count number of spikes
 *
 * If data is not valid, increment the spike counter for the specific channel in the analog array.
 *
 * @param a 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of analog array 
 * @param data_read 16-bit value new data to be added to the buffer
 * @param size 8-bit value that indicate number of analog array 
 *
 * @return uint8_t the number of spikes detected for the specific channel
 */
uint8_t spike_counter(Analog_t* a, uint8_t channel,  uint16_t data_read, uint8_t size);

/**
 * @brief Get media from three samples
 *
 * Calculate the average of the data in the FIFO buffer for a specific channel in the analog array.
 *
 * @param a 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of analog array 
 * @param size 8-bit value that indicate number of analog array 
 *
 * @return uint16_t the calculated average value
 */
uint16_t analog_get_media (Analog_t* a, uint8_t channel, uint8_t size);

/**
 * @brief Read data from analog pins
 *
 * Read data from the analog pins and store it in the FIFO buffer for each channel.
 *
 * @param a 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of analog array 
 * @param size 8-bit value that indicate number of analog array 
 *
 * @return void
 */
void analog_read_data (Analog_t* a, uint8_t channel, uint8_t size);

/**
 * @brief Print data for a specific channel
 *
 * Print the data stored in a specific channel in the analog array.
 *
 * @param a 8-bit struct pointer to an n-element data array
 * @param channel 8-bit value that indicate channel of analog array 
 *
 * @return void
 */
void analog_print(Analog_t* a, uint8_t channel);

#endif
