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
 * @file ble_hal.h
 * @brief this file contain the functions prototype to create an abstract interface 
 * to manage bluetooth low energy (BLE) communication
 *
 * The following functions will be implemented:
 * - ble_init() to initialize the ble
 * - ble_create_service() to create BLE service and characteristics
 * - ble_transmit_temp() to transmit temperature data over BLE
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */

#ifndef __BLE_HAL_H__
#define __BLE_HAL_H__

#include "common.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID   "906311b0-4d56-11eb-8404-0800200c9a66"
#define CHARACTERISTIC_UUID_TEMP  "4ac8a682-9736-4e5d-932b-e9b31405049c"
#define CHARACTERISTIC_UUID_HUMIDITY  "9ec13766-fec8-46c4-a280-6b0f9346dea0"
#define CHARACTERISTIC_UUID_SLRRAD  "e7924032-959e-4493-bd5c-0df9f1d225a3"

extern BLECharacteristic *characteristic_temp;
extern BLECharacteristic *characteristic_humidity;
extern BLECharacteristic *characteristic_slrrad;

extern bool deviceConnected;

/**
 * @brief Initialize bluetooth Low Energy (BLE)
 *
 * Initialize the Ble USING the BLEDevice library and set up the server, service, and characteristics.
 *
 * @param NO PARAMETERS
 *
 * @return void
 */
void ble_init();

/**
 * @brief Create BLE service and characteristics
 *
 * Create a BLE service and characteristics for transmitting sensor data and other information.
 *
 * @param NO PARAMETERS
 *
 * @return void
 */
void ble_create_service();

/**
 * @brief Transmit temperature data over BLE
 *
 * Transmit temperature data over BLE by setting the value of the characteristic and notifying connected devices.
 *
 * @param value 16-bit value representing the temperature data
 *
 * @return void
 */
void ble_transmit_temp(uint16_t value);

/**
 * @brief Transmit humidity percentage over BLE
 *
 * Transmit humidity percentage over BLE by setting the value of the characteristic and notifying connected devices.
 *
 * @param value 16-bit value representing the humidity data
 *
 * @return void
 */
void ble_transmit_humidity(uint16_t value);

/**
 * @brief Transmit solar radition status over BLE
 *
 * Transmit solar radition status over BLE by setting the value of the characteristic and notifying connected devices.
 *
 * @param value 16-bit value representing the solar radition data
 *
 * @return void
 */
void ble_transmit_slrrad(uint16_t value);


#endif
