#include "task_led.h"
#include "sensi_driver_error.h"
#include "sensi_interface_gpio.h"
#include <stddef.h>

sensi_driver_status_t task_led_init(void)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  err_code |= sensi_platform_gpio_init();
  uint8_t leds[] = SENSI_BOARD_LEDS_LIST;
  for(size_t ii = 0; ii < SENSI_BOARD_LEDS_NUMBER; ii++)
  {
    sensi_platform_gpio_configure(leds[ii], SENSI_INTERFACE_GPIO_MODE_OUTPUT_HIGHDRIVE);
    sensi_platform_gpio_write(leds[ii], !SENSI_BOARD_LEDS_ACTIVE_STATE);
  }

  return err_code;
}

sensi_driver_status_t task_led_write(uint8_t led, task_led_state_t state)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  err_code |= sensi_platform_gpio_write(led, state);
  return err_code;
}

sensi_driver_status_t task_led_cycle(void)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  static uint8_t phase = 0;
  uint8_t leds[] = SENSI_BOARD_LEDS_LIST;
  err_code |= sensi_platform_gpio_toggle(leds[phase++]);
  if(SENSI_BOARD_LEDS_NUMBER <= phase) { phase = 0; }
  return err_code;
}