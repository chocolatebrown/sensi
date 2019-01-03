/**
 * sensi log interface.
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 **/
#ifndef SENSI_INTERFACE_LOG_H
#define SENSI_INTERFACE_LOG_H

#include "sensi_driver_error.h"
#include "sensi_driver_sensor.h"
#include <stddef.h>

/**
 * Severity levels of log messages
 **/
typedef enum
{
  SENSI_INTERFACE_LOG_ERROR,
  SENSI_INTERFACE_LOG_WARNING,
  SENSI_INTERFACE_LOG_INFO,
  SENSI_INTERFACE_LOG_DEBUG,
}sensi_interface_log_severity_t;

/**
 * Runs initialization code for the logging backend and sets the severity level.
 *
 * parameter min_severity: least severe log level that will be printed.
 * returns SENSI_DRIVER_SUCCESS if log was init, error code otherwise
 */
sensi_driver_status_t sensi_platform_log_init(sensi_interface_log_severity_t min_severity);

/**
 * Blocks until remaining log messages are sent out
 *
 * returns SENSI_DRIVER_SUCCESS if buffered messages were sent, error otherwise.
 */
sensi_driver_status_t sensi_platform_log_flush(void);

/**
 * Queues messages into log. May block or may return as soon as data is in buffer being transferred out
 *
 * parameter severity: severity of the log message
 * parameter message: message string
 *
 */
void sensi_platform_log(sensi_interface_log_severity_t severity, const char* message);

/**
 * Write text description of error message into given string pointer and null-terminate it.
 * The string will be cut if it cannot fit into given space.
 *
 * parameter error: error code to convert to string
 * parameter error_string: pointer to character array where error should be written
 * parameter space_remaining: How many bytes there are remaining in the error string.
 * returns number of bytes written (snprintf rvalue).
 */
size_t sensi_platform_error_to_string(sensi_driver_status_t error, char* error_string, size_t space_remaining);

/**
 * Log the given configuration parameters at given log level.
 *
 * parameter level: Level of log. SENSI_INTERFACE_LOG_ (ERROR, WARNING, INFO, DEBUG)
 * parameter configuration: Configuration to print
 * parameter unit: String representation to the unit of a scale
 */
void sensi_interface_log_sensor_configuration(const sensi_interface_log_severity_t level, const sensi_driver_sensor_configuration_t* const configuration, const char* unit);

#endif