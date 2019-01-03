/**
 * Platform-independent helper functions for logging
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 **/

 #include "sensi_driver_error.h"
 #include "sensi_driver_sensor.h"
 #include "sensi_interface_log.h"
 #include <stdio.h>
 #include <string.h>
size_t sensi_platform_error_to_string(sensi_driver_status_t error, char* error_string, size_t space_remaining)
{
  if(NULL == error_string)
  {
    SENSI_DRIVER_ERROR_CHECK(SENSI_DRIVER_ERROR_NULL, SENSI_DRIVER_ERROR_NULL);
    return 0;
  }

  size_t written = 0;
  sensi_driver_status_t error_bit = 0;
  // Print each error individually
  do
  {
    // Print comma + space if needed
    if(written != 0)
    {
      written += snprintf(error_string + written, space_remaining - written, ", ");
    }
    // If there is some error, print the lowest bit and reset the lowest bit in error code.
    if(error)
    {
      for(uint8_t ii = 0; ii < 32; ii++)
      {
        if(error & (1<<ii))
        {
          error_bit = 1<<ii;
          error &= 0xFFFFFFFF-(1<<ii);
        }
      }
    }
    switch(error_bit)
    {
      case SENSI_DRIVER_SUCCESS:
        written += snprintf(error_string + written, space_remaining - written, "%s", "SUCCESS");
        break;

      case SENSI_DRIVER_ERROR_INTERNAL:
        written += snprintf(error_string + written, space_remaining - written, "%s", "INTERNAL");
        break;

      case SENSI_DRIVER_ERROR_NOT_FOUND:
        written += snprintf(error_string + written, space_remaining - written, "%s", "NOT_FOUND");
        break;

      case SENSI_DRIVER_ERROR_NO_MEM:
        written += snprintf(error_string + written, space_remaining - written, "%s", "NO_MEM");
        break;

      case SENSI_DRIVER_ERROR_NOT_SUPPORTED:
        written += snprintf(error_string + written, space_remaining - written, "%s", "NOT_SUPPORTED");
        break;

       case SENSI_DRIVER_ERROR_INVALID_STATE:
        written += snprintf(error_string + written, space_remaining - written, "%s", "INVALID_STATE");
        break;

      case SENSI_DRIVER_ERROR_INVALID_LENGTH:
        written += snprintf(error_string + written, space_remaining - written, "%s", "INVALID_LENGTH");
        break;

      case SENSI_DRIVER_ERROR_INVALID_FLAGS:
        written += snprintf(error_string + written, space_remaining - written, "%s", "INVALID_FLAGS");
        break;

      case SENSI_DRIVER_ERROR_INVALID_DATA:
        written += snprintf(error_string + written, space_remaining - written, "%s", "INVALID_DATA");
        break;

      case SENSI_DRIVER_ERROR_DATA_SIZE:
        written += snprintf(error_string + written, space_remaining - written, "%s", "DATA_SIZE");
        break;

      case SENSI_DRIVER_ERROR_TIMEOUT:
        written += snprintf(error_string + written, space_remaining - written, "%s", "TIMEOUT");
        break;

      case SENSI_DRIVER_ERROR_NULL:
        written += snprintf(error_string + written, space_remaining - written, "%s", "NULL");
        break;

      case SENSI_DRIVER_ERROR_FORBIDDEN:
        written += snprintf(error_string + written, space_remaining - written, "%s", "FORBIDDEN");
        break;

      case SENSI_DRIVER_ERROR_INVALID_ADDR:
        written += snprintf(error_string + written, space_remaining - written, "%s", "INVALID_ADDR");
        break;

      case SENSI_DRIVER_ERROR_BUSY:
        written += snprintf(error_string + written, space_remaining - written, "%s", "BUSY");
        break;

      case SENSI_DRIVER_ERROR_RESOURCES:
        written += snprintf(error_string + written, space_remaining - written, "%s", "RESOURCES");
        break;

      case SENSI_DRIVER_ERROR_NOT_IMPLEMENTED:
        written += snprintf(error_string + written, space_remaining - written, "%s", "NOT_IMPLEMENTED");
        break;

      case SENSI_DRIVER_ERROR_SELFTEST:
        written += snprintf(error_string + written, space_remaining - written, "%s", "SELFTEST");
        break;

      case SENSI_DRIVER_ERROR_FATAL:
        written += snprintf(error_string + written, space_remaining - written, "%s", "FATAL");
        break;

      default:
        written = snprintf(error_string + written, space_remaining - written, "%s", "UNKNOWN");
        break;
    }
  }while(error);
  return written;
}

// Convert configuration value to string.
static char* configuration_value_to_string(const uint8_t val)
{
  static char msg[17]; // sizeof "Not implemented", including NULL
  memset(msg, 0, sizeof(msg));
  if( val <= 200 && val > 0)
  {
    snprintf(msg, sizeof(msg), "%d", val);
  }
  else switch(val)
  {
    case SENSI_DRIVER_SENSOR_CFG_MIN:
      snprintf(msg, sizeof(msg), "MIN");
      break;

    case SENSI_DRIVER_SENSOR_CFG_MAX:
      snprintf(msg, sizeof(msg), "MAX");
      break;

    case SENSI_DRIVER_SENSOR_CFG_CONTINUOUS:
      snprintf(msg, sizeof(msg), "CONTINUOUS");
      break;

    case SENSI_DRIVER_SENSOR_CFG_DEFAULT:
      snprintf(msg, sizeof(msg), "DEFAULT");
      break;

    case SENSI_DRIVER_SENSOR_CFG_NO_CHANGE:
      snprintf(msg, sizeof(msg), "No change");
      break;

    case SENSI_DRIVER_SENSOR_CFG_ON_DRDY:
      snprintf(msg, sizeof(msg), "On data");
      break;

    case SENSI_DRIVER_SENSOR_CFG_ON_INTERRUPT:
      snprintf(msg, sizeof(msg), "On interrupt");
      break;

    case SENSI_DRIVER_SENSOR_CFG_SINGLE:
      snprintf(msg, sizeof(msg), "Single");
      break;

    case SENSI_DRIVER_SENSOR_CFG_SLEEP:
      snprintf(msg, sizeof(msg), "Sleep");
      break;

    case SENSI_DRIVER_SENSOR_ERR_NOT_SUPPORTED:
      snprintf(msg, sizeof(msg), "Not supported");
      break;

    case SENSI_DRIVER_SENSOR_ERR_NOT_IMPLEMENTED:
      snprintf(msg, sizeof(msg), "Not implemented");
      break;

     case SENSI_DRIVER_SENSOR_ERR_INVALID:
      snprintf(msg, sizeof(msg), "Invalid");
      break;

    default:
      snprintf(msg, sizeof(msg), "Unknown");
      break;
  }
  return msg;
}

void sensi_interface_log_sensor_configuration(const sensi_interface_log_severity_t level, const sensi_driver_sensor_configuration_t* const configuration, const char* unit)
{
  #define msg_size 128
  char msg[msg_size] = {0};
  snprintf(msg, msg_size, "Sample rate: %s Hz\r\n", configuration_value_to_string(configuration->samplerate));
  sensi_platform_log(level, msg);
  memset(msg, 0, sizeof(msg));

  snprintf(msg, msg_size, "Resolution:  %s bits\r\n", configuration_value_to_string(configuration->resolution));
  sensi_platform_log(level, msg);
  memset(msg, 0, sizeof(msg));

  snprintf(msg, msg_size, "Scale:       %s %s\r\n", configuration_value_to_string(configuration->scale), unit);
  sensi_platform_log(level, msg);
  memset(msg, 0, sizeof(msg));

  size_t written = snprintf(msg, msg_size, "DSP:         ");

  switch(configuration->dsp_function)
  {
    case SENSI_DRIVER_SENSOR_DSP_HIGH_PASS:
      written += snprintf(msg + written, msg_size - written, "High pass x ");
      break;

    case SENSI_DRIVER_SENSOR_DSP_IIR:
      written += snprintf(msg + written, msg_size - written, "Infinite Impulse Response x ");
      break;

    case SENSI_DRIVER_SENSOR_DSP_LAST:
      written += snprintf(msg + written, msg_size - written, "Last x ");
      break;

    case SENSI_DRIVER_SENSOR_DSP_LOW_PASS:
      written += snprintf(msg + written, msg_size - written, "Lowpass x ");
      break;

    case SENSI_DRIVER_SENSOR_DSP_OS:
      written += snprintf(msg + written, msg_size - written, "Oversampling x ");
      break;

    default:
      written += snprintf(msg + written, msg_size - written, "Unknown x");
      break;
  }
  snprintf(msg + written, msg_size - written, "%s\r\n", configuration_value_to_string(configuration->dsp_parameter));
  sensi_platform_log(level, msg);
  memset(msg, 0, sizeof(msg));

  written = snprintf(msg, msg_size, "Mode:        %s\r\n", configuration_value_to_string(configuration->mode));

  sensi_platform_log(level, msg);
}