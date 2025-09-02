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
 * @file analog_hal.c
 * @brief Abstraction of analog interface 
 *
 * This implementation file provides an abstraction interface to manage analog peripheral.
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */

#include "HAL/analog_hal.h"

Analog_t analog_a[NUM_ANALOG_PERIP] = {}; // array of analog peripherals

/***********************************************************
 Function Definitions
***********************************************************/
void analog_init(Analog_t* a, uint8_t size){

  for (int i = 0; i < size; i++)
  {
    a[i].pin = 0x00;
    a[i].status = true; 
    a[i].fbuf ={
      .length = BUFFER_SIZE, // Set the length of the buffer
      .data_set = {0x00, 0x00, 0x00, 0x00}, // Initialize data_set with zeros
      .data_media = 0, // Initialize data_media to zero
      .count = 0 // Initialize count to zero
    };
    a[i].counter_spike = NO_ADC_SPIKE;
  }
}

void analog_set_pin(Analog_t* a, uint8_t channel, uint8_t pin, uint8_t size){
	if(channel < size){
		if(pin != 0xFF){
      if(a[channel].status){ 
        a[channel].pin = pin;
      }
		}
	}
}

void Ff_buffer_add(Analog_t* a, uint8_t channel, uint16_t data_read, uint8_t size){
  if(channel < size){
    if(a[channel].status){
      if(a[channel].fbuf.count < a[channel].fbuf.length){
        a[channel].fbuf.data_set[a[channel].fbuf.count] = data_read; // Fill the buffer with the new data
        a[channel].fbuf.count++;
      }else{
        // Shift the buffer to make space for the new data
        for(uint8_t i = 0; i < a[channel].fbuf.length - 1; i++){
          a[channel].fbuf.data_set[i] = a[channel].fbuf.data_set[i + 1];
        }
        a[channel].fbuf.data_set[a[channel].fbuf.length - 1] = data_read; // Add the new data at the end
      }
    }
  }
}

bool data_is_valid(Analog_t* a, uint8_t channel, uint16_t data_read, uint8_t size){
   if(channel < size){
    if(a[channel].status){
      if(a[channel].fbuf.count == a[channel].fbuf.length){
        uint16_t last_value = a[channel].fbuf.data_set[a[channel].fbuf.count - 1]; // Get the last value in the buffer
        return (data_read <= last_value + RANGE & data_read >= last_value - RANGE);
      }else{
        // If the buffer is not full, consider the data valid
        return true;
      }
    }else{
      // If the channel is not valid, return false
      DEBUG_PRINT("Channel not valid %d\n", channel);
      return false; // If the channel is not valid, return false
    }
    
  }else{
    DEBUG_PRINT("Channel out of bounds %d\n", channel);
    // If the channel is out of bounds, return false
    return false; // If the channel is out of bounds, return false
  }
}


uint8_t spike_counter(Analog_t* a, uint8_t channel,  uint16_t data_read, uint8_t size){
  if(channel < size){
    if(a[channel].status){
      if(!data_is_valid(a, channel, data_read, size)){
          a[channel].counter_spike ++; // First spike detected
      }else{
          a[channel].counter_spike = NO_ADC_SPIKE; // Reset counter if data is valid
      }
    }
  }
  return a[channel].counter_spike;
}

void analog_read_data (Analog_t* a, uint8_t channel, uint8_t size){
  if (a[channel].status){
    uint16_t data_read = analogRead(a[channel].pin);
    if (spike_counter(a, channel, data_read, size) == NO_ADC_SPIKE || spike_counter(a, channel, data_read, size) >= LIMIT_ADC_SPIKE){
      Ff_buffer_add(a, channel, data_read, size); // Add new data to the FIFO buffer
      a[channel].counter_spike = NO_ADC_SPIKE; // Reset spike counter if data is valid
      a[channel].fbuf.data_media = analog_get_media(a, channel, size); // Calculate media from the buffer
    }
  }
}

uint16_t analog_get_media (Analog_t* a, uint8_t channel, uint8_t size){
  uint16_t media = 0;
  if(channel < size){
    if(a[channel].status){
      if(a[channel].fbuf.count > 0){
        uint16_t sum = 0;
        for(uint8_t i = 0; i < a[channel].fbuf.count; i++){
          sum += a[channel].fbuf.data_set[i]; // Sum all values in the buffer
        }
        media = sum / a[channel].fbuf.count; // Calculate the average
      }else{
        media = 0; // If no data, return zero
      }
    }
  }
  return media;
}


void analog_print(Analog_t* a, uint8_t channel){
  DEBUG_PRINT("%d \t %d \t [%d %d %d ",a[channel].pin,a[channel].status, a[channel].fbuf.count, a[channel].fbuf.length,a[channel].fbuf.data_media);
  for (uint8_t i = 0; i < a[channel].fbuf.count; i++){
    DEBUG_PRINT("%d",a[channel].fbuf.data_set[i]);
    if (i < a[channel].fbuf.count - 1) {
      DEBUG_PRINT(", ");
    }
  }
  DEBUG_PRINT("]\t%d\n", a[channel].counter_spike);
}