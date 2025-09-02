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
 * @file smart plant.h
 * @brief this file contain the functions prototype to manage the smart plant functionalities
 * 
 * The following functions will be implemented:
 * - smartplant_init() to initialize the smart plant data structure
 * - smartplant_set_temperature() to set the temperature for a specific plant
 * - smartplant_set_solar_intensity() to set the solar intensity for a specific plant
 * - smartplant_set_sand_humidity() to set the sand humidity for a specific plant
 * - smartplant_set_alarm() to set the alarm status for a specific plant
 * - smartplant_display_data() to display the data of a specific plant on the OLED screen
 * 
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */
#ifndef __SMARTPLANT_H__
#define __SMARTPLANT_H__

#include "common.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "peripheral.h"

#define NUM_PLANTS 1 // Number of smart plants

//OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

#define PLANT_1 0 // Plant channel
#define PLANT_2 1 // Plant channel Unused
#define PLANT_3 2 // Plant channel Unused
#define PLANT_4 3 // Plant channel Unused
#define PLANT_5 4 // Plant channel Unused


typedef struct
{
	float			temperature; // Temperature in Celsius
	float 		sand_humidity; // Sand humidity in percentage
  uint8_t   solar_intensity; // Solar intensity
  bool 			alarm; // Alarm status
}SmartPlant_t;

/**
 * @brief Initialize SmartPlant_t structure
 *
 * Initialize the smart plant data structure with default values.
 *
 * @param sm SmartPlant_t struct pointer
 * @param size 8-bit value that indicate number of plants
 *
 * @return void
 */
void smartplant_init(SmartPlant_t* sm, uint8_t size);

/**
 * @brief Set temperature for a specific plant
 *
 * Set the temperature for a specific plant in the smart plant data structure.
 *
 * @param sm SmartPlant_t struct pointer
 * @param channel 8-bit value that indicate channel of smart plant structure
 * @param size 8-bit value that indicate number of plants
 *
 * @return void
 */
void smartplant_set_temperature(SmartPlant_t* sm, uint8_t channel, uint8_t size);

/**
 * @brief Set solar intensity for a specific plant
 *
 * Set the solar intensity for a specific plant in the smart plant data structure.
 *
 * @param sm SmartPlant_t struct pointer
 * @param channel 8-bit value that indicate channel of smart plant structure
 * @param size 8-bit value that indicate number of plants
 * @param perip_ch 8-bit value that indicate channel of solar sensor peripheral
 *
 * @return void
 */
void smartplant_set_solar_intensity(SmartPlant_t* sm, uint8_t channel, uint8_t size, uint8_t perip_ch);

/**
 * @brief Set sand humidity for a specific plant
 *
 * Set the sand humidity for a specific plant in the smart plant data structure.
 *
 * @param sm SmartPlant_t struct pointer
 * @param channel 8-bit value that indicate channel of smart plant structure
 * @param size 8-bit value that indicate number of plants
 * @param perip_ch 8-bit value that indicate channel of humidity sensor peripheral
 *
 * @return void
 */
void smartplant_set_sand_humidity(SmartPlant_t* sm, uint8_t channel, uint8_t size, uint8_t perip_ch);

/**
 * @brief Set alarm status for a specific plant
 *
 * Set the alarm status for a specific plant in the smart plant data structure.
 * If the temperature exceeds a threshold, the alarm is activated.
 *
 * @param sm SmartPlant_t struct pointer
 * @param channel 8-bit value that indicate channel of smart plant structure
 * @param size 8-bit value that indicate number of plants
 * @param perip_ch 8-bit value that indicate channel of LED peripheral
 *
 * @return void
 */
void smartplant_set_alarm(SmartPlant_t* sm, uint8_t channel, uint8_t size, uint8_t perip_ch);

/**
 * @brief Display data of a specific plant on the OLED screen
 *
 * Display the temperature, solar intensity, and sand humidity of a specific plant
 * on the OLED screen.
 *
 * @param sm SmartPlant_t struct pointer
 * @param channel 8-bit value that indicate channel of smart plant structure
 * @param size 8-bit value that indicate number of plants
 *
 * @return void
 */
void smartplant_display_data(SmartPlant_t* sm, uint8_t channel, uint8_t size);


#endif  /* __SMART_PLANT_H__ */
