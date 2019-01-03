#include "application_config.h"
#include "sensi_boards.h"
#include "sensi_driver_error.h"
#include "sensi_driver_sensor.h"
#include "sensi_interface_bme280.h"
#include "sensi_interface_environmental_mcu.h"
#include "sensi_interface_log.h"
#include "sensi_interface_scheduler.h"
#include "sensi_interface_timer.h"
#include "task_environmental.h"
#include "task_led.h"

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>

SENSI_PLATFORM_TIMER_ID_DEF(environmental_timer);
static sensi_driver_sensor_t environmental_sensor = {0};

//handler for scheduled accelerometer event
static void task_environmental_scheduler_task(void *p_event_data, uint16_t event_size)
{
  // No action necessary
}

// Timer callback, schedule accelerometer event here.
static void task_environmental_timer_cb(void* p_context)
{
  sensi_platform_scheduler_event_put(NULL, 0, task_environmental_scheduler_task);
}

sensi_driver_status_t task_environmental_configure(sensi_driver_sensor_configuration_t* config)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  sensi_platform_log(SENSI_INTERFACE_LOG_INFO, "\r\nAttempting to configure environmental with:\r\n");
  // Use empty in place of unit
  sensi_interface_log_sensor_configuration(SENSI_INTERFACE_LOG_INFO, config, "");
  err_code |= environmental_sensor.configuration_set(&environmental_sensor, config);
  SENSI_DRIVER_ERROR_CHECK(err_code, ~SENSI_DRIVER_ERROR_FATAL);
  sensi_platform_log(SENSI_INTERFACE_LOG_INFO, "Actual configuration:\r\n");
  sensi_interface_log_sensor_configuration(SENSI_INTERFACE_LOG_INFO, config, "");
  return err_code;
}

sensi_driver_status_t task_environmental_init(void)
{
  // Assume "Not found", gets set to "Success" if a usable sensor is present
  sensi_driver_status_t err_code = SENSI_DRIVER_ERROR_NOT_FOUND;
  sensi_driver_bus_t bus = SENSI_DRIVER_BUS_NONE;
  sensi_driver_sensor_configuration_t config;
  config.samplerate    = APPLICATION_ENVIRONMENTAL_SAMPLERATE;
  config.resolution    = APPLICATION_ENVIRONMENTAL_RESOLUTION;
  config.scale         = APPLICATION_ENVIRONMENTAL_SCALE;
  config.dsp_function  = APPLICATION_ENVIRONMENTAL_DSPFUNC;
  config.dsp_parameter = APPLICATION_ENVIRONMENTAL_DSPPARAM;
  config.mode          = APPLICATION_ENVIRONMENTAL_MODE;
  uint8_t handle = 0;

  // Initialize timer for environmental task. Note: the timer is not started.
//  err_code |= sensi_platform_timer_create(&environmental_timer, SENSI_INTERFACE_TIMER_MODE_REPEATED, task_environmental_timer_cb);

  #if SENSI_BOARD_ENVIRONMENTAL_BME280_PRESENT
    err_code = SENSI_DRIVER_SUCCESS;
    // Only SPI supported for now
    bus = SENSI_DRIVER_BUS_SPI;
    handle = SENSI_BOARD_SPI_SS_ENVIRONMENTAL_PIN;
    err_code |= sensi_interface_bme280_init(&environmental_sensor, bus, handle);
    SENSI_DRIVER_ERROR_CHECK(err_code, SENSI_DRIVER_ERROR_NOT_FOUND);

    if(SENSI_DRIVER_SUCCESS == err_code)
    {
      err_code |= task_environmental_configure(&config);
      return err_code;
    }
  #endif

  #if SENSI_BOARD_ENVIRONMENTAL_MCU_PRESENT
    err_code = SENSI_DRIVER_SUCCESS;
    err_code |= sensi_interface_environmental_mcu_init(&environmental_sensor, bus, handle);
    SENSI_DRIVER_ERROR_CHECK(err_code, SENSI_DRIVER_SUCCESS);
    if(SENSI_DRIVER_SUCCESS == err_code)
    {
      err_code |= task_environmental_configure(&config);
      return err_code;
    }
  #endif

  return SENSI_DRIVER_ERROR_NOT_FOUND;
}

sensi_driver_status_t task_environmental_sample(void)
{
  if(NULL == environmental_sensor.mode_set) { return SENSI_DRIVER_ERROR_INVALID_STATE; }
  uint8_t mode = SENSI_DRIVER_SENSOR_CFG_SINGLE;
  return environmental_sensor.mode_set(&mode);
}

sensi_driver_status_t task_environmental_data_log(const sensi_interface_log_severity_t level)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  sensi_interface_environmental_data_t data;
  if(NULL == environmental_sensor.data_get) { return SENSI_DRIVER_ERROR_INVALID_STATE; }

  // If the mode is single, take a new sample.
  if(APPLICATION_ENVIRONMENTAL_MODE == SENSI_DRIVER_SENSOR_CFG_SINGLE)
  {
    err_code |= task_environmental_sample();
  }

  err_code |= environmental_sensor.data_get(&data);
  char message[128] = {0};
  snprintf(message, sizeof(message), "Time: %lu\r\n", (uint32_t)(data.timestamp_ms&0xFFFFFFFF));
  sensi_platform_log(level, message);
  snprintf(message, sizeof(message), "Temperature: %.2f\r\n", data.temperature_c);
  sensi_platform_log(level, message);
  snprintf(message, sizeof(message), "Pressure: %.2f\r\n" ,data.pressure_pa);
  sensi_platform_log(level, message);
  snprintf(message, sizeof(message), "Humidity: %.2f\r\n", data.humidity_rh);
  sensi_platform_log(level, message);
  return err_code;
}

sensi_driver_status_t task_environmental_data_get(sensi_interface_environmental_data_t* const data)
{
  if(NULL == data) { return SENSI_DRIVER_ERROR_NULL; }
  if(NULL == environmental_sensor.data_get) { return SENSI_DRIVER_ERROR_INVALID_STATE; }
  return environmental_sensor.data_get(data);
}

sensi_driver_status_t task_environmental_on_button(void)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  err_code |= task_environmental_data_log(SENSI_INTERFACE_LOG_INFO);
  return err_code;
}