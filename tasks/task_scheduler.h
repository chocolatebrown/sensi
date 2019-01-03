/**
 * sensi Firmware 3.x Scheduler tasks.
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 **/

#ifndef  TASK_SCHEDULER_H
#define  TASK_SCHEDULER_H

#include "sensi_boards.h"
#include "sensi_driver_error.h"
#include "sensi_driver_sensor.h"
//#include "sensi_interface_adc.h"
#include "sensi_interface_log.h"

/**
 * Initializes scheduler
 *
 * returns SENSI_DRIVER_SUCCESS on success, error code from stack on error
 */
sensi_driver_status_t task_scheduler_init(void);

#endif