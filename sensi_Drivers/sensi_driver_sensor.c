#include "sensi_driver_error.h"
#include "sensi_driver_sensor.h"
#include <stddef.h>

sensi_driver_status_t sensi_driver_sensor_configuration_set(const sensi_driver_sensor_t* sensor, sensi_driver_sensor_configuration_t* config)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  if(NULL == sensor || NULL == config) { return SENSI_DRIVER_ERROR_NULL; }
  if(NULL == sensor->samplerate_set) { return SENSI_DRIVER_ERROR_INVALID_STATE; }
  err_code |= sensor->samplerate_set(&(config->samplerate));
  err_code |= sensor->resolution_set(&(config->resolution));
  err_code |= sensor->scale_set(&(config->scale));
  err_code |= sensor->dsp_set(&(config->dsp_function), &(config->dsp_parameter));
  err_code |= sensor->mode_set(&(config->mode));
  return err_code;
}

sensi_driver_status_t sensi_driver_sensor_configuration_get(const sensi_driver_sensor_t* sensor, sensi_driver_sensor_configuration_t* config)
{
  sensi_driver_status_t err_code = SENSI_DRIVER_SUCCESS;
  if(NULL == sensor || NULL == config) { return SENSI_DRIVER_ERROR_NULL; }
  if(NULL == sensor->samplerate_set) { return SENSI_DRIVER_ERROR_INVALID_STATE; }
  err_code |= sensor->samplerate_get(&(config->samplerate));
  err_code |= sensor->resolution_get(&(config->resolution));
  err_code |= sensor->scale_get(&(config->scale));
  err_code |= sensor->dsp_get(&(config->dsp_function), &(config->dsp_parameter));
  err_code |= sensor->mode_get(&(config->mode));
  return err_code;
}

static sensi_driver_sensor_timestamp_fp millis = NULL;

sensi_driver_status_t sensi_driver_sensor_timestamp_function_set(sensi_driver_sensor_timestamp_fp timestamp_fp)
{
  millis = timestamp_fp;
  return SENSI_DRIVER_SUCCESS;
}

// Calls the timestamp function and returns it's value. returns SENSI_DRIVER_UINT64_INVALID if timestamp function is NULL
uint64_t sensi_driver_sensor_timestamp_get(void)
{
  if(NULL == millis)
  {
    return SENSI_DRIVER_UINT64_INVALID;
  }
  return millis();
}