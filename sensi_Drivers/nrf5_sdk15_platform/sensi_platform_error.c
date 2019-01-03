/**
 * Convert NRF SDK errors to SENSI errors
 *
 * License: BSD-3
 * Author Otso Jousimaa <otso@ojousima.net>
 */

#include "sensi_platform_external_includes.h"
#if NRF5_SDK15_PLATFORM_ENABLED
#include "sensi_driver_error.h"
#include "sensi_interface_log.h"

#include "sdk_errors.h"
#include "nrf_nvic.h"

#include <stdio.h>
#include <string.h>

sensi_driver_status_t sensi_platform_to_sensi_error(void* error)
{
  ret_code_t err_code = *(ret_code_t*)error;
  if(NRF_SUCCESS == err_code)              { return SENSI_DRIVER_SUCCESS; }
  if(NRF_ERROR_INTERNAL == err_code)       { return SENSI_DRIVER_ERROR_INTERNAL; }
  if(NRF_ERROR_NO_MEM == err_code)         { return SENSI_DRIVER_ERROR_NO_MEM; }
  if(NRF_ERROR_NOT_FOUND == err_code)      { return SENSI_DRIVER_ERROR_NOT_FOUND; }
  if(NRF_ERROR_NOT_SUPPORTED == err_code)  { return SENSI_DRIVER_ERROR_NOT_SUPPORTED; }
  if(NRF_ERROR_INVALID_PARAM == err_code)  { return SENSI_DRIVER_ERROR_INVALID_PARAM; }
  if(NRF_ERROR_INVALID_STATE == err_code)  { return SENSI_DRIVER_ERROR_INVALID_STATE; }
  if(NRF_ERROR_INVALID_LENGTH == err_code) { return SENSI_DRIVER_ERROR_INVALID_LENGTH; }
  if(NRF_ERROR_INVALID_FLAGS == err_code)  { return SENSI_DRIVER_ERROR_INVALID_FLAGS; }
  if(NRF_ERROR_DATA_SIZE == err_code)      { return SENSI_DRIVER_ERROR_DATA_SIZE; }
  if(NRF_ERROR_TIMEOUT == err_code)        { return SENSI_DRIVER_ERROR_TIMEOUT; }
  if(NRF_ERROR_NULL == err_code)           { return SENSI_DRIVER_ERROR_NULL; }
  if(NRF_ERROR_FORBIDDEN == err_code)      { return SENSI_DRIVER_ERROR_FORBIDDEN; }
  if(NRF_ERROR_INVALID_ADDR == err_code)   { return SENSI_DRIVER_ERROR_INVALID_ADDR; }
  if(NRF_ERROR_BUSY == err_code)           { return SENSI_DRIVER_ERROR_BUSY; }
  if(NRF_ERROR_RESOURCES == err_code)      { return SENSI_DRIVER_ERROR_RESOURCES; }
  return SENSI_DRIVER_ERROR_INTERNAL;
}



void sensi_driver_error_check(sensi_driver_status_t error, sensi_driver_status_t non_fatal_mask, const char* file, int line)
{
  char message[NRF_LOG_BUFSIZE];
  size_t index = 0;
  // Cut out the full path
  const char* filename = strrchr(file, '/');
  // If on Windows
  if(NULL == filename) { filename = strrchr(file, '\\'); }
  // In case the file was already only the name
  if(NULL == filename) { filename = file; }
  // Otherwise skip the slash
  else{ filename++; }

  // Reset on fatal error
  if(~non_fatal_mask & error)
  {
    index += snprintf(message, sizeof(message), "%s:%d FATAL: ", filename, line);
    index += sensi_platform_error_to_string(error, (message + index), (sizeof(message) - index));
    snprintf((message + index), (sizeof(message) - index), "\r\n");
    sensi_platform_log(SENSI_INTERFACE_LOG_ERROR, message);
    sensi_platform_log_flush();
    NVIC_SystemReset();
  }
  // Log non-fatal errors
  else if(SENSI_DRIVER_SUCCESS != error)
  {
    index += snprintf(message, sizeof(message), "%s:%d WARNING: ", filename, line);
    index += sensi_platform_error_to_string(error, (message + index), (sizeof(message) - index));
    snprintf((message + index), (sizeof(message) - index), "\r\n");
    sensi_platform_log(SENSI_INTERFACE_LOG_WARNING, message);
  }
  // Do nothing on success
}

#endif