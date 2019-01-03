/**
 * sensi Firmware 3.x Environmental tasks.
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 **/

#ifndef  TASK_ENVIRONMENTAL_H
#define  TASK_ENVIRONMENTAL_H

#include "sensi_boards.h"
#include "sensi_driver_error.h"
#include "sensi_driver_sensor.h"
#include "sensi_interface_bme280.h"
#include "sensi_interface_environmental.h"
#include "sensi_interface_environmental_mcu.h"
#include "sensi_interface_log.h"

/**
 * Auto-detects and initializes environmental sensor in low-power state
 * Reads supported sensors from board.h and tries to initialize them.
 * Configures the sensor according to defaults in application_config.h
 */
sensi_driver_status_t task_environmental_init(void);

/**
 * Prints environmental data to log at given severity
 */
sensi_driver_status_t task_environmental_data_log(const sensi_interface_log_severity_t level);

/**
 * Get latest sample from the sensor. Remember to trigger sampling in case you're in single-shot mode
 */
sensi_driver_status_t task_environmental_data_get(sensi_interface_environmental_data_t* const data);

/**
 * Blink RED led for the duration of task. Get environmental data and print it on console.
 */
sensi_driver_status_t task_environmental_on_button(void);

/**
 *  Command environmental sensor to take a single sample. Leaves sensor in sleep
 **/
sensi_driver_status_t task_environmental_sample(void);


#endif