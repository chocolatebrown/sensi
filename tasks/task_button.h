#ifndef TASK_BUTTON_H
#define TASK_BUTTON_H

#include "sensi_boards.h"
#include "sensi_driver_error.h"
#include "sensi_interface_gpio_interrupt.h"

typedef sensi_driver_status_t(*task_button_fp_t)(void);

/**
 * Button initialization function. Configures GPIO as pulled-up interrupt input.
 *
 * parameter slope: slopes to interrupt on. (SENSI_INTERFACE_GPIO_SLOPE_)HITOLO, LOTOHI or TOGGLE
 * parameter action: Function to be called when button interrupt occurs
 *
 * return: Status code from the stack. SENSI_DRIVER_SUCCESS if no errors occured.
 **/
sensi_driver_status_t task_button_init(sensi_interface_gpio_slope_t slope, task_button_fp_t action);

/**
 * Calls other Button tasks.
 *
 * return: Status code from the stack. SENSI_DRIVER_SUCCESS if no errors occured.
 */
sensi_driver_status_t task_button_on_press(void);

#endif