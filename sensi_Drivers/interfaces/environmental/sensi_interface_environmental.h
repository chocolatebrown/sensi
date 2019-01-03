/**
 * Environmental data format
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */
#ifndef SENSI_INTERFACE_ENVIRONMENTAL_H
#define SENSI_INTERFACE_ENVIRONMENTAL_H
#include "sensi_driver_error.h"
#include <stdint.h>

#define SENSI_INTERFACE_ENVIRONMENTAL_INVALID SENSI_DRIVER_FLOAT_INVALID

typedef struct
{
  uint64_t timestamp_ms; // ms since boot
  float temperature_c;   // C
  float humidity_rh;     // RH-%
  float pressure_pa;     // Pa
}sensi_interface_environmental_data_t;

#endif