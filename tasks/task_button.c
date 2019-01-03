#include "sensi_driver_error.h"
#include "sensi_boards.h"
#include "sensi_interface_gpio.h"
#include "sensi_interface_yield.h"
#include "task_button.h"

static task_button_fp_t button_callback = NULL;
static sensi_interface_gpio_interrupt_fp_t interrupt_table[SENSI_BOARD_GPIO_NUMBER + 1 ] = {0};

// Wrapper to interrupt function
static void on_button(sensi_interface_gpio_evt_t event)
{
  if(NULL != button_callback) { button_callback(); }
}

sensi_driver_status_t task_button_init(sensi_interface_gpio_slope_t slope, task_button_fp_t action)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  button_callback = action;
  err_code |= sensi_platform_gpio_interrupt_init(interrupt_table, sizeof(interrupt_table));
  err_code |= sensi_platform_gpio_interrupt_enable(SENSI_BOARD_BUTTON_1, slope, SENSI_INTERFACE_GPIO_MODE_INPUT_PULLUP, on_button);
  return err_code;
}

