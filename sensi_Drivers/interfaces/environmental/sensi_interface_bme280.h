/**
 * Define environmental sensor abstraction functions for BME280
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */

#ifndef SENSI_INTERFACE_BME280_H
#define SENSI_INTERFACE_BME280_H
#include "sensi_driver_error.h"
#include "sensi_driver_sensor.h"

void bosch_delay_ms(uint32_t time_ms);
sensi_driver_status_t sensi_interface_bme280_init(sensi_driver_sensor_t* environmental_sensor, sensi_driver_bus_t bus, uint8_t handle);
sensi_driver_status_t sensi_interface_bme280_uninit(sensi_driver_sensor_t* environmental_sensor, sensi_driver_bus_t bus, uint8_t handle);
sensi_driver_status_t sensi_interface_bme280_samplerate_set(uint8_t* samplerate);
sensi_driver_status_t sensi_interface_bme280_samplerate_get(uint8_t* samplerate);
sensi_driver_status_t sensi_interface_bme280_resolution_set(uint8_t* resolution);
sensi_driver_status_t sensi_interface_bme280_resolution_get(uint8_t* resolution);
sensi_driver_status_t sensi_interface_bme280_scale_set(uint8_t* scale);
sensi_driver_status_t sensi_interface_bme280_scale_get(uint8_t* scale);
sensi_driver_status_t sensi_interface_bme280_dsp_set(uint8_t* dsp, uint8_t* parameter);
sensi_driver_status_t sensi_interface_bme280_dsp_get(uint8_t* dsp, uint8_t* parameter);
sensi_driver_status_t sensi_interface_bme280_mode_set(uint8_t*);
sensi_driver_status_t sensi_interface_bme280_mode_get(uint8_t*);
sensi_driver_status_t sensi_interface_bme280_data_get(void* data);

#endif