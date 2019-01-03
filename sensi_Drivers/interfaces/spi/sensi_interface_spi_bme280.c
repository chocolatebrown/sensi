/**
 * sensi spi interface for bme280
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 **/
#include <stdint.h>
#include <string.h> //memcpy

#include "sensi_boards.h"
#include "sensi_driver_error.h"
#include "sensi_interface_gpio.h"
#include "sensi_interface_spi.h"
#include "sensi_interface_yield.h"


int8_t sensi_interface_spi_bme280_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  err_code |= sensi_platform_gpio_write(dev_id, SENSI_INTERFACE_GPIO_LOW);
  err_code |= sensi_platform_spi_xfer_blocking(&reg_addr, 1, NULL, 0);
  err_code |= sensi_platform_spi_xfer_blocking(reg_data, len, NULL, 0);
  err_code |= sensi_platform_gpio_write(dev_id, SENSI_INTERFACE_GPIO_HIGH);
  return (SENSI_DRIVER_SUCCESS == err_code) ? 0 : -1;
}

int8_t sensi_interface_spi_bme280_read (uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  err_code |= sensi_platform_gpio_write(dev_id, SENSI_INTERFACE_GPIO_LOW);
  err_code |= sensi_platform_spi_xfer_blocking(&reg_addr, 1, NULL, 0);
  err_code |= sensi_platform_spi_xfer_blocking(NULL, 0, reg_data, len);
  err_code |= sensi_platform_gpio_write(dev_id, SENSI_INTERFACE_GPIO_HIGH);
  return (SENSI_DRIVER_SUCCESS == err_code) ? 0 : -1;
}