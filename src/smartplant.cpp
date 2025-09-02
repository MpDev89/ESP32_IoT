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
 * @file smart_plant.c
 * @brief Monitoring and manage smart plant data
 *
 * This implementation file provides the functions to monitor and manage smart plant data.
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */
#include "smartplant.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SmartPlant_t SM_list[NUM_PLANTS] = {};

/***********************************************************
 Function Definitions
***********************************************************/
void smartplant_init(SmartPlant_t* sm, uint8_t size){
  for (int i = 0; i < size; i++)  {
    sm[i].temperature = 0.0f; // Initialize temperature to 0.0
    sm[i].sand_humidity = 0.0f; // Initialize sand humidity to 0.0
    sm[i].solar_intensity = 0; // Initialize solar intensity to 0 
    sm[i].alarm = false; // Initialize alarm status to false
  }
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C or 0x3D
    Serial.println("OLED not found");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Smart Plant Monitor");
  display.display();
}

void smartplant_set_temperature(SmartPlant_t* sm, uint8_t channel, uint8_t size) {
  if(channel < size){
    sm[channel].temperature = get_temperature(); // Read temperature from the sensor
  }
}

void smartplant_set_solar_intensity(SmartPlant_t* sm, uint8_t channel, uint8_t size, uint8_t perip_ch) {
  if(channel < size){
    sm[channel].solar_intensity = read_solar_radiation(perip_ch); // Read solar intensity from the sensor
  }
}

void smartplant_set_sand_humidity(SmartPlant_t* sm, uint8_t channel, uint8_t size, uint8_t perip_ch) {
  if(channel < size){
    sm[channel].sand_humidity = read_humidity(perip_ch); // Read sand humidity from the sensor
  }
}

void smartplant_set_alarm(SmartPlant_t* sm, uint8_t channel, uint8_t size, uint8_t perip_ch) {
  if(channel < size){
    if (sm[channel].temperature > 30.0f) {
      turn_led(perip_ch, true); // Turn on the LED if alarm is active
      sm[channel].alarm = true; // Set the alarm status
    } else {
      turn_led(perip_ch, false); // Turn off the LED if alarm is inactive
      sm[channel].alarm = false; // Set the alarm status
    }
  }
}

void smartplant_display_data(SmartPlant_t* sm, uint8_t channel, uint8_t size) {
  if(channel < size){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Smart Plant Monitor");
    display.setCursor(0,10);
    display.print("Temp: ");
    display.print(sm[channel].temperature);
    display.println(" C");
    display.setCursor(0,20);
    display.print("Solar intensity ");
    if (sm[channel].solar_intensity == 1) {
        display.println("Low");
    } else {
        display.println("High");
    }
    display.setCursor(0,31);
    display.print("Sand Humidity: ");
    display.print(sm[channel].sand_humidity);
    display.println("%");
    
    display.display();
  }
}