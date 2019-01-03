#include "sensi_platform_external_includes.h"
#if NRF5_SDK15_SCHEDULER_ENABLED

#include "sensi_driver_error.h"
#include "sensi_interface_scheduler.h"
#include "sdk_errors.h"
#include "app_scheduler.h"

// Ignore give parameters to call the macro with #defined constants
sensi_driver_status_t sensi_interface_scheduler_init(size_t event_size, size_t queue_length)
{
  // Event size and queue length must be fixed at compile time. Warn user if other values are going to be used.
  if(event_size != NRF5_SDK15_SCHEDULER_DATA_MAX_SIZE || queue_length != NRF5_SDK15_SCHEDULER_QUEUE_MAX_LENGTH)
  { SENSI_DRIVER_ERROR_CHECK(SENSI_DRIVER_ERROR_INVALID_PARAM, ~SENSI_DRIVER_ERROR_FATAL); }

  APP_SCHED_INIT(NRF5_SDK15_SCHEDULER_DATA_MAX_SIZE, NRF5_SDK15_SCHEDULER_QUEUE_MAX_LENGTH);
  return SENSI_DRIVER_SUCCESS;
}

sensi_driver_status_t sensi_platform_scheduler_execute (void)
{
  app_sched_execute();
  return SENSI_DRIVER_SUCCESS;
}

sensi_driver_status_t sensi_platform_scheduler_event_put (void const *p_event_data, uint16_t event_size, sensi_scheduler_event_handler_t handler)
{
  ret_code_t err_code = app_sched_event_put(p_event_data, event_size, (app_sched_event_handler_t) handler);
  return sensi_platform_to_sensi_error(&err_code);
}

#endif