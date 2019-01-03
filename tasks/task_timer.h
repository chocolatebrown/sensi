/**
 * sensi Firmware 3.x Timer tasks.
 *
 * License: BSD-3
 * Author: Ramsay
 **/

#ifndef  TASK_TIMER_H
#define  TASK_TIMER_H

#include "sensi_driver_error.h"
#include "sensi_interface_timer.h"

/**
 * Initializes the timer driver.
 *
 * Returns SENSI_DRIVER_SUCCESS on success, error code on error
 */
sensi_driver_status_t task_timer_init(void);


#endif