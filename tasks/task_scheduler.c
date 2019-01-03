#include "application_config.h"
#include "sensi_driver_error.h"
#include "sensi_interface_scheduler.h"
#include "task_scheduler.h"

sensi_driver_status_t task_scheduler_init(void)
{
  return sensi_interface_scheduler_init(APPLICATION_TASK_DATA_MAX_SIZE, APPLICATION_TASK_QUEUE_MAX_LENGTH);
}