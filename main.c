#include "application_config.h"
#include "sensi_interface_log.h"
#include "sensi_interface_yield.h"
#include "sensi_boards.h"
#include "task_led.h"
#include "task_button.h"
#include "task_spi.h"
#include "task_environmental.h"

#include <stdio.h>

int main(void)
{
  // Init logging
  sensi_driver_status_t status = SENSI_DRIVER_SUCCESS;
  status |= sensi_platform_log_init(APPLICATION_LOG_LEVEL);
  SENSI_DRIVER_ERROR_CHECK(status, SENSI_DRIVER_SUCCESS);

  sensi_platform_log(SENSI_INTERFACE_LOG_INFO, "Program start \r\n");

  // Init yield
  status |= sensi_platform_yield_init();
  SENSI_DRIVER_ERROR_CHECK(status, SENSI_DRIVER_SUCCESS);

  // Init GPIO
  status |= sensi_platform_gpio_init();
  SENSI_DRIVER_ERROR_CHECK(status, SENSI_DRIVER_SUCCESS);

  // Initialize LED gpio pins, turn RED led on.
  status |= task_led_init();
  status |= task_led_write(SENSI_BOARD_LED_RED, TASK_LED_ON);

  //Init Button with led_cycle_task
  status |= task_button_init(SENSI_INTERFACE_GPIO_SLOPE_HITOLO, task_environmental_on_button);
  SENSI_DRIVER_ERROR_CHECK(status, SENSI_DRIVER_SUCCESS);

  //Initialize SPI
  status |= task_spi_init();
  SENSI_DRIVER_ERROR_CHECK(status, SENSI_DRIVER_SUCCESS);

  //Initialize environmental- nRF52
  status |= task_environmental_init();
  SENSI_DRIVER_ERROR_CHECK(status, SENSI_DRIVER_SUCCESS);

  status |= task_led_write(SENSI_BOARD_LED_RED, TASK_LED_OFF);

  if(SENSI_DRIVER_SUCCESS == status)
  {
    status |= task_led_write(SENSI_BOARD_LED_GREEN, TASK_LED_ON);
  }

  sensi_platform_delay_ms(1000);
  status |= task_led_write(SENSI_BOARD_LED_GREEN, TASK_LED_OFF);
  
  while(1)
  {
    sensi_platform_log(SENSI_INTERFACE_LOG_INFO," Going to sleep\r\n");
    sensi_platform_yield();
    sensi_platform_log(SENSI_INTERFACE_LOG_INFO, "Waking up \r\n");
   }
}