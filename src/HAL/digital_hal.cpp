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
 * @file digital_hal.c
 * @brief Abstraction of digital interface 
 *
 * This implementation file provides an abstraction interface to manage digital peripheral.
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */
#include "HAL/digital_hal.h"


Dig_t digital_a[NUM_DIG_PERIP] = {};

/***********************************************************
 Function Definitions
***********************************************************/
void digital_init(Dig_t* d, uint8_t size){
  for (int i = 0; i < size; i++){
    d[i].pin = 0x00;
    d[i].status = true;
    d[i].direction = false;
    d[i].value = false;
  }
}

void digital_set_pin(Dig_t* d, uint8_t channel, uint8_t pin, uint8_t size){
	if(channel < size){
		if(pin != 0xFF){
      if(d[channel].status){ 
        d[channel].pin = pin;
        pinMode(pin, d[channel].direction ? OUTPUT : INPUT); // Set pin mode based on direction
      }
		}
	}
}

void digital_set_direction(Dig_t* d, uint8_t channel, bool direction, uint8_t size){
	if(channel < size){
    if(d[channel].status){ 
			d[channel].direction = direction;
      pinMode(d[channel].pin, direction ? OUTPUT : INPUT); // Set pin mode based on direction
    }
	}
}

void digital_set_value(Dig_t* d, uint8_t channel, bool value, uint8_t size){
  if(channel < size){
		if(d[channel].status){
      d[channel].value = value;
      if (value)
			  digitalWrite(d[channel].pin, HIGH);
      else
        digitalWrite(d[channel].pin, LOW);
		}
	}
}

int digital_read(Dig_t* d, uint8_t channel, uint8_t size){
  int value = -1;
  if(channel < size){
		if(d[channel].status){
      value = digitalRead(d[channel].pin);
		}
	}
  return value;
}


void digital_print(Dig_t* d, uint8_t channel){
  DEBUG_PRINT("%d \t %d \t %d \t %d \n",d[channel].pin,d[channel].status, d[channel].direction, d[channel].value);
}
