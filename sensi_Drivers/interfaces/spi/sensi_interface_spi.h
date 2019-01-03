/**
 * SENSI spi interface.
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 **/

#ifndef SENSI_INTERFACE_SPI_H
#define SENSI_INTERFACE_SPI_H
#include "sensi_driver_error.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
  SENSI_INTERFACE_SPI_MODE_0,
  SENSI_INTERFACE_SPI_MODE_1,
  SENSI_INTERFACE_SPI_MODE_2,
  SENSI_INTERFACE_SPI_MODE_3
}sensi_interface_spi_mode_t;

typedef enum {
  SENSI_INTERFACE_SPI_FREQUENCY_1M,
  SENSI_INTERFACE_SPI_FREQUENCY_2M,
  SENSI_INTERFACE_SPI_FREQUENCY_4M,
  SENSI_INTERFACE_SPI_FREQUENCY_8M,
}sensi_interface_spi_frequency_t;

typedef struct{
  uint8_t mosi;                              // pin number of MOSI
  uint8_t miso;                              // pin number of MISO
  uint8_t sclk;                              // pin number of SCLK
  uint8_t* ss_pins;                          // array of SPI pins, can be freed after function exits
  uint8_t ss_pins_number;                    // sizeof ss_pins
  sensi_interface_spi_frequency_t frequency;
  sensi_interface_spi_mode_t mode;
}sensi_interface_spi_init_config_t;

/**
 * Initialize SPI driver with default settings
 *
 * parameter config: Configuration of the SPI peripheral. Will setup given slave select pins as outputs.
 * returns error code from the stack, SENSI_DRIVER_SUCCESS if no error occurred
 **/
 sensi_driver_status_t sensi_platform_spi_init(const sensi_interface_spi_init_config_t* config);

/**
 * Full-duplex SPI. Clocks out MAX(tx_len, rx_len) bytes. It is allowed to send different length transactions, tx will clock out 0xFF if there is
 * less bytes in TX than RX. Does not use slave select pins. RX will start at the same time as TX, i.e. one byte address + read commands will generally have
 * {0x00, data} in rx buffer. Function is blocking and will not sleep while transaction is ongoing.
 *
 * parameter tx: pointer to data to be sent, can be NULL if tx_len is 0.
 * parameter tx_len: length of data to be sent
 * parameter rx: pointer to data to be received, can be NULL if rx_len is 0.
 * parameter rx_len: length of data to be received
 *
 **/
sensi_driver_status_t sensi_platform_spi_xfer_blocking(const uint8_t* tx, const size_t tx_len, uint8_t* rx, const size_t rx_len);
#endif