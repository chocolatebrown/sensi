/**
 *  Define environmental sensor abstraction functions for onboard MCU
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */

#ifndef SENSI_INTERFACE_ENVIRONMENTAL_MCU_H
#define SENSI_INTERFACE_ENVIRONMENTAL_MCU_H
#include "sensi_driver_error.h"
#include "sensi_driver_sensor.h"

sensi_driver_status_t sensi_interface_environmental_mcu_init(sensi_driver_sensor_t* environmental_sensor, sensi_driver_bus_t, uint8_t handle);
sensi_driver_status_t sensi_interface_environmental_mcu_uninit(sensi_driver_sensor_t* environmental_sensor, sensi_driver_bus_t, uint8_t handle);
sensi_driver_status_t sensi_interface_environmental_mcu_samplerate_set(uint8_t* samplerate);
sensi_driver_status_t sensi_interface_environmental_mcu_samplerate_get(uint8_t* samplerate);
sensi_driver_status_t sensi_interface_environmental_mcu_resolution_set(uint8_t* resolution);
sensi_driver_status_t sensi_interface_environmental_mcu_resolution_get(uint8_t* resolution);
sensi_driver_status_t sensi_interface_environmental_mcu_scale_set(uint8_t* scale);
sensi_driver_status_t sensi_interface_environmental_mcu_scale_get(uint8_t* scale);
sensi_driver_status_t sensi_interface_environmental_mcu_dsp_set(uint8_t* dsp, uint8_t* parameter);
sensi_driver_status_t sensi_interface_environmental_mcu_dsp_get(uint8_t* dsp, uint8_t* parameter);
sensi_driver_status_t sensi_interface_environmental_mcu_mode_set(uint8_t*);
sensi_driver_status_t sensi_interface_environmental_mcu_mode_get(uint8_t*);
sensi_driver_status_t sensi_interface_environmental_mcu_data_get(void* data);

#endif