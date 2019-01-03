/**
 * Timer abstraction. Allows creating single-shot and repeated timers which call a function at interval.
 * Timer IDs must be defined with PLATFORM_TIMER_ID_DEF(timer_id)
 * The timer will schedule the functions to run, so there might be a lot of jitter in timeout.
 */

#ifndef SENSI_INTERFACE_TIMER_H
#define SENSI_INTERFACE_TIMER_H

#include "sensi_driver_error.h"
#include "sensi_platform_timer.h"
#include <stdbool.h>

typedef enum {
  SENSI_INTERFACE_TIMER_MODE_SINGLE_SHOT,
  SENSI_INTERFACE_TIMER_MODE_REPEATED
}sensi_interface_timer_mode_t;

/**
 * Function to be called when timer event occurs.
 */
typedef void(*sensi_timer_timeout_handler_t)(void* p_context);

// Calls whatever initialization is required by application timers
sensi_driver_status_t sensi_platform_timers_init(void);

//return true if timers have been successfully initialized.
bool sensi_platform_timers_is_init(void);

/* Function for creating a timer instance
 *
 * @param p_timer_id pointer to timer id, outputs ID which can be used to control the timer
 * @param mode mode of the timer, single shot or repeated
 * @param timeout_handler function which gets called
 */
sensi_driver_status_t sensi_platform_timer_create(sensi_platform_timer_id_t const *p_timer_id, sensi_interface_timer_mode_t mode, sensi_timer_timeout_handler_t timeout_handler);

/**
 * Start given timer at a mode defined in sensi_platform_timer_create. This operation is ignored if timer is already running.
 *
 * @param timer_id id of timer to control
 * @param timeout (or interval) of timer in milliseconds
 *
 * Return SENSI_DRIVER_SUCCESS on success, error code on start.
 */
sensi_driver_status_t sensi_platform_timer_start (sensi_platform_timer_id_t timer_id, uint32_t ms);

/**
 * Stop a running timer.
 *
 * @param timer_id id of timer to stop
 * returns SENSI_DRIVER_SUCCESS on success, error code from stack on error
 */
sensi_driver_status_t sensi_platform_timer_stop (sensi_platform_timer_id_t timer_id);

#endif