/**
 * GPIO implementations on Nordic SDK15.
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */

#include "sensi_platform_external_includes.h"
#if NRF5_SDK15_GPIO_ENABLED
#include "sensi_interface_gpio.h"
#include "sensi_driver_error.h"
#include "nrf_gpio.h"
#include <stdbool.h>

// No implementation required.
sensi_driver_status_t sensi_platform_gpio_init(void)
{
  return SENSI_DRIVER_SUCCESS;
}

sensi_driver_status_t sensi_platform_gpio_configure(uint8_t pin, sensi_interface_gpio_mode_t mode)
{
  if(SENSI_INTERFACE_GPIO_PIN_UNUSED == pin) { return SENSI_DRIVER_SUCCESS; }
  switch (mode)
  {
  case SENSI_INTERFACE_GPIO_MODE_HIGH_Z:
    nrf_gpio_cfg_default(pin);
    break;

  case SENSI_INTERFACE_GPIO_MODE_INPUT_NOPULL:
    nrf_gpio_cfg_input (pin, NRF_GPIO_PIN_NOPULL);
    break;

  case SENSI_INTERFACE_GPIO_MODE_INPUT_PULLUP:
    nrf_gpio_cfg_input (pin, NRF_GPIO_PIN_PULLUP);
    break;

  case SENSI_INTERFACE_GPIO_MODE_INPUT_PULLDOWN:
    nrf_gpio_cfg_input (pin, NRF_GPIO_PIN_PULLDOWN);
    break;

  case SENSI_INTERFACE_GPIO_MODE_OUTPUT_STANDARD:
    nrf_gpio_cfg_output (pin);
    break;

  case SENSI_INTERFACE_GPIO_MODE_OUTPUT_HIGHDRIVE:
    nrf_gpio_cfg (pin,
                  NRF_GPIO_PIN_DIR_OUTPUT,
                  NRF_GPIO_PIN_INPUT_DISCONNECT,
                  NRF_GPIO_PIN_NOPULL,
                  NRF_GPIO_PIN_H0H1,
                  NRF_GPIO_PIN_NOSENSE);
    break;

  default:
    return SENSI_DRIVER_ERROR_INVALID_PARAM;
  }
  return SENSI_DRIVER_SUCCESS;
}

sensi_driver_status_t sensi_platform_gpio_toggle(uint8_t pin)
{
    nrf_gpio_pin_toggle(pin);
    return SENSI_DRIVER_SUCCESS;
}

sensi_driver_status_t sensi_platform_gpio_write(uint8_t pin, sensi_interface_gpio_state_t state)
{
  if(SENSI_INTERFACE_GPIO_HIGH == state) { nrf_gpio_pin_set(pin);   }
  if(SENSI_INTERFACE_GPIO_LOW  == state) { nrf_gpio_pin_clear(pin); }
  return SENSI_DRIVER_SUCCESS;
}

sensi_driver_status_t sensi_platform_gpio_read(uint8_t pin, sensi_interface_gpio_state_t* state)
{
  if(NULL == state) { return SENSI_DRIVER_ERROR_NULL; }
  bool high = nrf_gpio_pin_read(pin);
  if(true == high)  { *state = SENSI_INTERFACE_GPIO_HIGH; }
  if(false == high) { *state = SENSI_INTERFACE_GPIO_LOW;  }
  return SENSI_DRIVER_SUCCESS;
}

#endif