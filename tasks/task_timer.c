#include "sensi_driver_error.h"
#include "sensi_interface_timer.h"
#include "task_timer.h"

sensi_driver_status_t task_timer_init(void)
{
  return sensi_platform_timers_init();
}