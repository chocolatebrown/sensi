/**
 * Interface to the scheduler
 *
 * Execute scheduled tasks in round-robin order.
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */

#ifndef SENSI_INTERFACE_SCHEDULER_H
#define SENSI_INTERFACE_SCHEDULER_H

#include "sensi_driver_error.h"
#include <stddef.h>

/**
 * Initialize scheduler.
 *
 * Allocates memory for scheduler task queue.
 *
 * parameter max_event_size: maximum size for event data
 * parameter queue_size: maximum number of scheduled tasks
 *
 * Returns SENSI_DRIVER_SUCCESS on success, error code from stack on error
 */
sensi_driver_status_t sensi_interface_scheduler_init(size_t event_size, size_t queue_size);

/**
 * Type definition for scheduler event handler.
 *
 * parameter p_event_data: Data for the event handler
 * parameter event_size: Size of the event data. Must be smaller than or equal to max_event_size
 *
 */
typedef void(*sensi_scheduler_event_handler_t)(void *p_event_data, uint16_t event_size);

/**
 *  Executes all scheduled tasks. If task schedules itself to be run immediately this will be run in a never-ending loop, without sleeping.
 *
 *  Returns SENSI_DRIVER_SUCCESS if queue was executed successfully.
 *  Returns error code from the stack if error occurs.
 */
sensi_driver_status_t sensi_platform_scheduler_execute(void);

/**
 * Schedule given task to be executed on next call to sensi_platform_scheduler_execute
 */
sensi_driver_status_t sensi_platform_scheduler_event_put (void const *p_event_data, uint16_t event_size, sensi_scheduler_event_handler_t handler);



#endif