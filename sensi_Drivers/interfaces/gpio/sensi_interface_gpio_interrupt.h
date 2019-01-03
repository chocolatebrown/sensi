/**
 * GPIO interrupt definitions
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */
#ifndef SENSI_INTERFACE_PIN_INTERRUPT_H
#define SENSI_INTERFACE_PIN_INTERRUPT_H

#include "nrf_drv_gpiote.h"

#include "sensi_driver_error.h"
#include "sensi_interface_gpio.h"

typedef enum 
{
  SENSI_INTERFACE_GPIO_SLOPE_HITOLO,
  SENSI_INTERFACE_GPIO_SLOPE_LOTOHI,
  SENSI_INTERFACE_GPIO_SLOPE_TOGGLE,
  SENSI_INTERFACE_GPIO_SLOPE_UNKNOWN
}sensi_interface_gpio_slope_t;

typedef struct 
{
  sensi_interface_gpio_slope_t slope;
  uint8_t pin;
}sensi_interface_gpio_evt_t;

typedef void(*sensi_interface_gpio_interrupt_fp_t)(const sensi_interface_gpio_evt_t);

/**
 * Initialize interrupt functionality to GPIO. Takes address of interrupt table as a pointer to avoid tying driver into a specific board with a specific number of GPIO
 * pins and to avoid including boards repository within the driver.
 *
 * parameter interrupt_table: Array of function pointers, initialized to all nulls. Size should be the number of GPIO+1, i.e. SENSI_BOARD_GPIO_NUMBER + 1.
 * parameter max_interrupts: Size of interrupt table. 
 *
 * Return SENSI_DRIVER_SUCCESS on success, error code on failure.
 */
sensi_driver_status_t sensi_platform_gpio_interrupt_init(sensi_interface_gpio_interrupt_fp_t* interrupt_table, uint8_t max_interrupts);

/**
 * Enable interrupt on a pin.
 *
 * parameter pin: pin to use as interrupt source
 * parameter slope: slope to interrupt on
 * parameter mode: GPIO input mode. Must be (SENSI_INTERFACE_GPIO_)INPUT_PULLUP, INPUT_PULLDOWN or INPUT_NOPULL
 * parameter handler: function pointer which will be called with sensi_interface_gpio_evt_t as a parameter on interrupt.
 *
 * Return SENSI_DRIVER_SUCCESS on success, error code on failure.
 */
sensi_driver_status_t sensi_platform_gpio_interrupt_enable(uint8_t pin, 
                                                           sensi_interface_gpio_slope_t slope, 
                                                           sensi_interface_gpio_mode_t mode, 
                                                           sensi_interface_gpio_interrupt_fp_t handler);

#endif