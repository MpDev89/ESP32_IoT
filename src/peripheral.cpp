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
 * @file peripheral.c
 * @brief peripheral function declaration linked to functionalities
 *
 * This implementation file provides function to set up the peripheral pins based on the functionalities required by the system.
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */
#include "HAL/digital_hal.h"
#include "peripheral.h"
#include "HAL/analog_hal.h"
#include "HAL/task_hal.h"
#include "HAL/ble_hal.h"

extern Dig_t digital_a[NUM_DIG_PERIP]; // array of digital peripherals
extern Analog_t analog_a[NUM_ANALOG_PERIP]; // array of digital peripherals

Adafruit_BMP280 bmp; // I2C interface

/***********************************************************
 Function Definitions
***********************************************************/
void peripheral_init() {
    // Initialize the digital array
    digital_init(digital_a, NUM_DIG_PERIP);
    analog_init(analog_a, NUM_ANALOG_PERIP);
   
    // Set up DIODE_LED pin
    digital_set_pin(digital_a, DIODE_LED_1_ch, DIODE_LED_1_pin, NUM_DIG_PERIP);
    digital_set_direction(digital_a, DIODE_LED_1_ch, true, NUM_DIG_PERIP); // Set as output
    

    // Set up SOLAR_SNS pin
    digital_set_pin(digital_a, SOLAR_SNS_1_ch, SOLAR_SNS_1_pin, NUM_DIG_PERIP);
    digital_set_direction(digital_a, SOLAR_SNS_1_ch, false, NUM_DIG_PERIP); // Set as input

    // Set up HUMIDITY pin
    analog_set_pin(analog_a, HUMIDITY_1_ch, HUMIDITY_1_pin, NUM_ANALOG_PERIP); // Set pin for humidity sensor


    if (!bmp.begin(0x76)) { // 0x76 or 0x77 depending on sensor
      Serial.println("Could not find BMP280 sensor!");
      while (true);
   }
   ble_init();
 }

 void turn_led(uint8_t channel, bool value) {
    digital_set_value(digital_a, channel, value, NUM_DIG_PERIP); // Set initial value to HIGH
    //digital_print(&digital_a[DIODE_LED_1_ch], DIODE_LED_1_ch); // Print status of the LED
 } 

float get_temperature(){
   float temperature = bmp.readTemperature(); // Read temperature from BMP280
   DEBUG_PRINT("Temperature: %4.4f *C\n",temperature);
   return temperature; // Return the temperature value
}

int read_solar_radiation(uint8_t channel) {
    int solarSts = digital_read(digital_a, channel, NUM_DIG_PERIP);
    DEBUG_PRINT("Solar sensor status = %d \n", solarSts);
   return solarSts; // Return the status of the solar sensor
}

float read_humidity(uint8_t channel){
   float humidity_value = 0.0F;
   analog_read_data(analog_a,channel, NUM_ANALOG_PERIP); 
   uint16_t media = analog_get_media(analog_a, channel, NUM_ANALOG_PERIP); // Get the average value from the humidity sensor
   humidity_value = (float)media * (100.0f / 4095.0f); // Convert the average value to percentage
   DEBUG_PRINT("Humidity sensor value = %.2f %%\n", humidity_value); 
   //analog_print(analog_a, channel); // Print status of the humidity sensor
   return humidity_value; 
}


