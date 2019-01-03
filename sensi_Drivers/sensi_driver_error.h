/**
 * SENSI error codes and error check function
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 **/

#ifndef SENSI_DRIVER_ERROR_H
#define SENSI_DRIVER_ERROR_H

#include <float.h>
#include <stdint.h>

#define SENSI_DRIVER_FLOAT_INVALID  FLT_MAX
#define SENSI_DRIVER_UINT64_INVALID UINT64_MAX

#define SENSI_DRIVER_SUCCESS               0
#define SENSI_DRIVER_ERROR_INTERNAL        1  ///< Internal Error
#define SENSI_DRIVER_ERROR_NO_MEM          2  ///< No Memory for operation
#define SENSI_DRIVER_ERROR_NOT_FOUND       3  ///< Not found
#define SENSI_DRIVER_ERROR_NOT_SUPPORTED   4  ///< Not supported
#define SENSI_DRIVER_ERROR_INVALID_PARAM   5  ///< Invalid Parameter
#define SENSI_DRIVER_ERROR_INVALID_STATE   6  ///< Invalid state, operation disallowed in this state
#define SENSI_DRIVER_ERROR_INVALID_LENGTH  7  ///< Invalid Length
#define SENSI_DRIVER_ERROR_INVALID_FLAGS   8 ///< Invalid Flags
#define SENSI_DRIVER_ERROR_INVALID_DATA    9  ///< Invalid Data
#define SENSI_DRIVER_ERROR_DATA_SIZE       10  ///< Invalid Data size
#define SENSI_DRIVER_ERROR_TIMEOUT         11 ///< Operation timed out
#define SENSI_DRIVER_ERROR_NULL            12 ///< Null Pointer
#define SENSI_DRIVER_ERROR_FORBIDDEN       13 ///< Forbidden Operation
#define SENSI_DRIVER_ERROR_INVALID_ADDR    14 ///< Bad Memory Address
#define SENSI_DRIVER_ERROR_BUSY            15 ///< Busy
#define SENSI_DRIVER_ERROR_RESOURCES       16 ///< Not enough resources for operation
#define SENSI_DRIVER_ERROR_NOT_IMPLEMENTED 17 ///< Not implemented yet
#define SENSI_DRIVER_ERROR_SELFTEST        18 ///< Self-test fail
#define SENSI_DRIVER_STATUS_MORE_AVAILABLE 19 ///< Driver has more data queued
#define SENSI_DRIVER_ERROR_FATAL           20 ///< Program should always reset after this

typedef int32_t sensi_driver_status_t;

/**
 * Convert error code from platform to Sensi error code.
 *
 * parameter error: Error code from platform
 * return: Most descriptive sensi_driver_status_t code of the platform error.
 **/
sensi_driver_status_t sensi_platform_to_sensi_error(void* error);

/**
 * Check given error code and compare it to non-fatal errors.
 *
 * If error is considered fatal (or not non-fatal), reset the device
 * If the error is non-fatal, log an error on the console and return
 *
 * parameter error: error code, might have several flags in it.
 * parameter non_fatal_mask: Signal that this error is acceptable for program flow and execution may continue.
 * parameter file: file from which function was called
 * parameter line: line from which the function was called
 **/
void sensi_driver_error_check(sensi_driver_status_t error, sensi_driver_status_t non_fatal_mask, const char* file, int line);

// Shorthand macro for calling the error check function with current file & line
#define SENSI_DRIVER_ERROR_CHECK(error, mask) sensi_driver_error_check(error, mask, __FILE__, __LINE__)

#endif