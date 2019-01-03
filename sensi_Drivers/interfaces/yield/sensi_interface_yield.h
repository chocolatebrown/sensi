/**
 * Yield and delay function definitions.
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */

#ifndef SENSI_INTERFACE_YIELD_H
#define SENSI_INTERFACE_YIELD_H
#include "sensi_driver_error.h"

/** 
 * Initializes yield, for example inits CPU usage timers.
 *
 * Returns SENSI_SUCCESS if no error occured, error code otherwise.
 **/
sensi_driver_status_t sensi_platform_yield_init(void);

/** 
  * Function which will release execution / go to sleep until next event occurs.
  *
  * Returns SENSI_SUCCESS if no error occured, error code otherwise.
  **/
sensi_driver_status_t sensi_platform_yield(void);

/** 
  * Delay a given number of milliseconds.
  *
  * Return SENSI_SUCCESS on success, error code otherwise.
  **/
sensi_driver_status_t sensi_platform_delay_ms(uint32_t time);

/** 
  * Delay a given number of microseconds.
  *
  * Return SENSI_SUCCESS on success, error code otherwise.
  **/
sensi_driver_status_t sensi_platform_delay_us(uint32_t time);

#endif