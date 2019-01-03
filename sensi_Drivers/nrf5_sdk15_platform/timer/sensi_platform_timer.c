#include "sensi_platform_external_includes.h"
#if NRF5_SDK15_TIMER_ENABLED
#include "sensi_driver_error.h"
#include "sensi_interface_timer.h"

#include "nrf_error.h"
#include "nrf_drv_clock.h"
#include "sdk_errors.h"
#include "app_timer.h"

#include <stdbool.h>

static bool m_is_init = false;

sensi_driver_status_t sensi_platform_timers_init(void)
{
  if (m_is_init) { return SENSI_DRIVER_SUCCESS; }
  ret_code_t err_code = NRF_SUCCESS;

  // Initialize clock if not already initialized
  if(false == nrf_drv_clock_init_check()){ err_code |= nrf_drv_clock_init(); }
  nrf_drv_clock_lfclk_request(NULL);

  err_code |= app_timer_init();
  if (NRF_SUCCESS == err_code) { m_is_init = true; }
  return sensi_platform_to_sensi_error(&err_code);
}

//return true if timers have been successfully initialized.
bool sensi_platform_timers_is_init(void)
{
  return m_is_init;
}

sensi_driver_status_t sensi_platform_timer_create (sensi_platform_timer_id_t const *p_timer_id, sensi_interface_timer_mode_t mode, sensi_timer_timeout_handler_t timeout_handler)
{
  app_timer_mode_t nrf_mode = APP_TIMER_MODE_SINGLE_SHOT;
  if (SENSI_INTERFACE_TIMER_MODE_REPEATED == mode) { nrf_mode = APP_TIMER_MODE_REPEATED; }

  ret_code_t err_code = app_timer_create (p_timer_id,
                        nrf_mode,
                        (app_timer_timeout_handler_t)timeout_handler);
  return sensi_platform_to_sensi_error(&err_code);
}

sensi_driver_status_t sensi_platform_timer_start (sensi_platform_timer_id_t timer_id, uint32_t ms)
{
  ret_code_t err_code = app_timer_start(timer_id, APP_TIMER_TICKS(ms), NULL);
  return sensi_platform_to_sensi_error(&err_code);

}

sensi_driver_status_t sensi_platform_timer_stop (sensi_platform_timer_id_t timer_id)
{
  ret_code_t err_code = app_timer_stop(timer_id);
  return sensi_platform_to_sensi_error(&err_code);
}

#endif