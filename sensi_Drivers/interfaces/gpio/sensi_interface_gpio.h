/**
 * GPIO definitions
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */

#ifndef SENSI_INTERFACE_GPIO_H
#define SENSI_INTERFACE_GPIO_H

#include "sensi_driver_error.h"
#include <stdbool.h>

#define SENSI_INTERFACE_GPIO_PIN_UNUSED 0xFF // Use this value to signal that nothing should be done with this pin, i.e. UART CTS not used.

typedef enum
{
  SENSI_INTERFACE_GPIO_MODE_HIGH_Z,
  SENSI_INTERFACE_GPIO_MODE_INPUT_NOPULL,
  SENSI_INTERFACE_GPIO_MODE_INPUT_PULLUP,
  SENSI_INTERFACE_GPIO_MODE_INPUT_PULLDOWN,
  SENSI_INTERFACE_GPIO_MODE_OUTPUT_STANDARD,
  SENSI_INTERFACE_GPIO_MODE_OUTPUT_HIGHDRIVE
}sensi_interface_gpio_mode_t;

typedef enum
{
  SENSI_INTERFACE_GPIO_LOW = false,
  SENSI_INTERFACE_GPIO_HIGH = true
}sensi_interface_gpio_state_t;

/**
 * Initializes GPIO module
 *
 * Return SENSI_DRIVER_SUCCESS on success, error code on failure.
 */
sensi_driver_status_t sensi_platform_gpio_init(void);

/**
 * Configure a pin of a port into a mode.
 * If there are several ports the platform driver must implement a conversion function from port + pin to uint8_t.
 *
 * Parameter pin:  Pin number
 * Parameter mode: mode to set the pin to.
 *
 * Return SENSI_DRIVER_SUCCESS on success, error code on failure.
 */
sensi_driver_status_t sensi_platform_gpio_configure(uint8_t pin, sensi_interface_gpio_mode_t mode);

/**
 * Toggle the state of a pin of a port.
 * If there are several ports the platform driver must implement a conversion function from port + pin to uint8_t.
 *
 * Parameter pin:  Pin number
 *
 * Return SENSI_DRIVER_SUCCESS on success, error code on failure.
 * May return SENSI_DRIVER_ERROR_INVALID_STATE if pin was not set as an output.
 */
sensi_driver_status_t sensi_platform_gpio_toggle(uint8_t pin);

/**
 * Write a pin of a port into given state
 * If there are several ports the platform driver must implement a conversion function from port + pin to uint8_t.
 *
 * Parameter pin:   Pin number
 * Parameter state: State to which the pin should be set to.
 *
 * Return SENSI_DRIVER_SUCCESS on success, error code on failure.
 * May return SENSI_DRIVER_ERROR_INVALID_STATE if pin was not set as an output.
 */
sensi_driver_status_t sensi_platform_gpio_write(uint8_t pin, sensi_interface_gpio_state_t state);

/**
 * Read state of a pin of a port into bool high
 * If there are several ports the platform driver must implement a conversion function from port + pin to uint8_t.
 *
 * Parameter pin:  Pin number
 * Parameter state: pointer to a SENSI_interface_gpio_state_t which will be set to the state of the pin.
 *
 * Return SENSI_DRIVER_SUCCESS on success, error code on failure.
 * Must return SENSI_DRIVER_ERROR_NULL if *state is a null pointer.
 * May return SENSI_DRIVER_ERROR_INVALID_ADDRESS if pointer is invalid for any reason.
 * May return SENSI_DRIVER_ERROR_INVALID_STATE if pin was not set as an input.
 */
sensi_driver_status_t sensi_platform_gpio_read(uint8_t pin, sensi_interface_gpio_state_t* state);

#endif