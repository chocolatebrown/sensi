/**
 *  Functions for printing out log via preferred method, i.e. RTT, UART or BLE.
 *
 *  Logging should implement well-defined overflow behaviour, i.e. block or drop new / drop old
 *  if log buffer gets filled.
 *
 *  Logging requires init and platform_log_level -functions.
 *  log must support levels ERROR, INFO, DEBUG.
 *
 *  Any prefixes, linenumbers etc are implemented at interface level and backend should print out raw data.
 *
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 **/

#include "sensi_driver_error.h"
#include "sensi_interface_log.h"
#include "sensi_interface_yield.h"
#include "sensi_platform_external_includes.h"
#include <stdarg.h>

#if NRF5_SDK15_LOG_ENABLED
#define NRF_LOG_MODULE_NAME sensi_log
#define NRF_LOG_LEVEL 3
#include "nrf_log.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_ctrl.h"
NRF_LOG_MODULE_REGISTER();

static sensi_interface_log_severity_t log_level;
sensi_driver_status_t sensi_platform_log_init(sensi_interface_log_severity_t min_severity)
{
  log_level = min_severity;
  NRF_LOG_INIT(NULL);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  return SENSI_DRIVER_SUCCESS;
}

sensi_driver_status_t sensi_platform_log_flush(void)
{
  NRF_LOG_FLUSH();
  sensi_platform_delay_ms(5);
  return SENSI_DRIVER_SUCCESS;
}

void sensi_platform_log(sensi_interface_log_severity_t severity, const char* message)
{
  if(NULL == message)
  {
    SENSI_DRIVER_ERROR_CHECK(SENSI_DRIVER_ERROR_NULL, SENSI_DRIVER_ERROR_NULL);
    return; 
  }

  if(log_level >= severity)
  {
    NRF_LOG_INTERNAL_RAW_INFO("%s", message);
  }
}
#endif