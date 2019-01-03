/**
 * Yield and delay function implementations on Nordic SDK15.
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */

#include "sensi_platform_external_includes.h"
#ifdef NRF5_SDK15_YIELD_ENABLED
#include "sensi_interface_yield.h"
#include "sensi_driver_error.h"
#include "nrf_delay.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_error.h"

sensi_driver_status_t sensi_platform_yield_init(void)
{
  ret_code_t err_code = nrf_pwr_mgmt_init();
  return sensi_platform_to_sensi_error(&err_code);
}

sensi_driver_status_t sensi_platform_yield(void)
{
  nrf_pwr_mgmt_run();
  return SENSI_DRIVER_SUCCESS;
}

sensi_driver_status_t sensi_platform_delay_ms(uint32_t time)
{
  nrf_delay_ms(time);
  return SENSI_DRIVER_SUCCESS;
}

sensi_driver_status_t sensi_platform_delay_us(uint32_t time)
{
  nrf_delay_us(time);
  return SENSI_DRIVER_SUCCESS;
}

#endif