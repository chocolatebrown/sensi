
#include "sensi_boards.h"
#include "sensi_driver_error.h"
#include "sensi_interface_log.h"
#include "sensi_interface_spi.h"
#include "task_spi.h"

sensi_driver_status_t task_spi_init(void)
{
  sensi_interface_spi_init_config_t config;
  uint8_t ss_pins[] = SENSI_BOARD_SPI_SS_LIST;
  config.mosi = SENSI_BOARD_SPI_MOSI_PIN;
  config.miso = SENSI_BOARD_SPI_MISO_PIN;
  config.sclk = SENSI_BOARD_SPI_SCLK_PIN;
  config.ss_pins = ss_pins;
  config.ss_pins_number = sizeof(ss_pins);
  // Assume mode 0 always.
  config.mode = SENSI_INTERFACE_SPI_MODE_0;
  switch(SENSI_BOARD_SPI_FREQ)
  {
    case SENSI_BOARD_SPI_FREQUENCY_1M:
      config.frequency = SENSI_INTERFACE_SPI_FREQUENCY_1M;
      break;

    case SENSI_BOARD_SPI_FREQUENCY_2M:
      config.frequency = SENSI_INTERFACE_SPI_FREQUENCY_2M;
      break;

    case SENSI_BOARD_SPI_FREQUENCY_4M:
      config.frequency = SENSI_INTERFACE_SPI_FREQUENCY_4M;
      break;

    case SENSI_BOARD_SPI_FREQUENCY_8M:
      config.frequency = SENSI_INTERFACE_SPI_FREQUENCY_8M;
      break;

    default:
      config.frequency = SENSI_INTERFACE_SPI_FREQUENCY_1M;
      sensi_platform_log(SENSI_INTERFACE_LOG_WARNING, "Unknown SPI frequency, defaulting to 1M\r\n");
  }
  return sensi_platform_spi_init(&config);
}