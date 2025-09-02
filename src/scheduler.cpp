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
 * @brief functions to manage scheduler
 *
 * This implementation file provides scheduler functions to manage tasks and their execution.
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */

#include "scheduler.h"
#include "HAL/ble_hal.h"
#include "peripheral.h"
#include "smartplant.h"

extern Task_t task_a[NUM_TASKS];
extern SmartPlant_t SM_list[NUM_PLANTS];


void Task1(void *pvParameters) {
  const TickType_t interval = pdMS_TO_TICKS(TASK1_TIME); // 1s
  TickType_t xLastWakeTime = xTaskGetTickCount();
  while (true) {
    Serial.printf("%lu - Task 1 completed on core %d\n", millis(), xPortGetCoreID());
    smartplant_set_temperature(SM_list, PLANT_1, NUM_PLANTS);
    smartplant_set_solar_intensity(SM_list, PLANT_1, NUM_PLANTS, SOLAR_SNS_1_ch);
    smartplant_set_sand_humidity(SM_list, PLANT_1, NUM_PLANTS, HUMIDITY_1_ch);
    smartplant_set_alarm(SM_list, PLANT_1, NUM_PLANTS, DIODE_LED_1_ch);
    smartplant_display_data(SM_list,PLANT_1, NUM_PLANTS); // Display data on OLED
    vTaskDelayUntil(&xLastWakeTime, interval);
  }
}

void Task2(void *pvParameters) {
  const TickType_t interval = pdMS_TO_TICKS(TASK2_TIME); // 3s
  TickType_t xLastWakeTime = xTaskGetTickCount();
  while (true) {
    Serial.printf("%lu - Task 2 completed on core %d\n", millis(), xPortGetCoreID());
    if (deviceConnected) {
      ble_transmit_temp((uint16_t)SM_list[PLANT_1].temperature);
      ble_transmit_humidity((uint16_t)SM_list[PLANT_1].sand_humidity);
      ble_transmit_slrrad((uint16_t)SM_list[PLANT_1].solar_intensity);
    }
    vTaskDelayUntil(&xLastWakeTime, interval);
  }
}

/***********************************************************
 Function Definitions
***********************************************************/
void scheduler_init() {
    // Initialize the digital array
    task_init(task_a, NUM_TASKS);
    // Set up tasks
    task_set_priority(task_a, TASK1_ch, TASK1_PRIO, NUM_TASKS); // Set priority for Task 1
    task_set_function(task_a, TASK1_ch, Task1, NUM_TASKS); // Set function for Task 1
    task_set_time(task_a, TASK1_ch, TASK1_TIME, NUM_TASKS); // Set time for Task 1
    task_set_priority(task_a, TASK2_ch, TASK2_PRIO, NUM_TASKS); // Set priority for Task 2
    task_set_function(task_a, TASK2_ch, Task2, NUM_TASKS); // Set function for Task 2
    task_set_time(task_a, TASK2_ch, TASK2_TIME, NUM_TASKS); // Set time for Task 2
    peripheral_init();
    smartplant_init(SM_list, NUM_PLANTS); // Initialize smart plant data

    xTaskCreatePinnedToCore(Task1, "Task 1", 2048, NULL, BaseType_t(get_task_priority(task_a, TASK1_ch, NUM_TASKS)) , NULL, 1); //Core 1
    xTaskCreatePinnedToCore(Task2, "Task 2", 2048, NULL, BaseType_t(get_task_priority(task_a, TASK2_ch, NUM_TASKS)) , NULL, 1); //Core 1
}



