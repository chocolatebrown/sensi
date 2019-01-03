#ifndef SENSI_BOARD_SENSITAG_H
#define SENSI_BOARD_SENSITAG_H

// LED definitions for SensiTag
#define SENSI_BOARD_LEDS_NUMBER               2
#define SENSI_BOARD_LED_1                     13
#define SENSI_BOARD_LED_2                     14
#define SENSI_BOARD_LEDS_ACTIVE_STATE         0
#define SENSI_BOARD_LEDS_LIST                 { SENSI_BOARD_LED_1, SENSI_BOARD_LED_2 }
#define SENSI_BOARD_LED_RED                   SENSI_BOARD_LED_1
#define SENSI_BOARD_LED_GREEN                 SENSI_BOARD_LED_2

// Button definitions for Sensitag
#define SENSI_BOARD_BUTTONS_NUMBER            1
#define SENSI_BOARD_BUTTON_1                  11
#define SENSI_BOARD_BUTTONS_ACTIVE_STATE      0
#define SENSI_BOARD_BUTTONS_LIST              { SENSI_BOARD_BUTTON_1 }
#define SENSI_BOARD_BUTTON_DEBOUNCE_PERIOD_MS 50

// Total number of GPIO pins
#define SENSI_BOARD_GPIO_NUMBER               32

// SPI definitions for SensiTag
#define SENSI_BOARD_SPI_SCLK_PIN              3 // SPI clock GPIO pin number.
#define SENSI_BOARD_SPI_MOSI_PIN              4 // SPI Master Out Slave In GPIO pin number.
#define SENSI_BOARD_SPI_MISO_PIN              28 // SPI Master In Slave Out GPIO pin number.
#define SENSI_BOARD_SPI_SS_ACCELEROMETER_PIN  8  // SPI Slave Select (accelerometer)
#define SENSI_BOARD_SPI_SS_ENVIRONMENTAL_PIN  29  // SPI Slave Select (BME280)
#define SENSI_BOARD_SPI_SS_LIST               {SENSI_BOARD_SPI_SS_ACCELEROMETER_PIN, SENSI_BOARD_SPI_SS_ENVIRONMENTAL_PIN}
#define SENSI_BOARD_SPI_FREQUENCY_1M          0
#define SENSI_BOARD_SPI_FREQUENCY_2M          1
#define SENSI_BOARD_SPI_FREQUENCY_4M          2
#define SENSI_BOARD_SPI_FREQUENCY_8M          3
#define SENSI_BOARD_SPI_FREQ                  SENSI_BOARD_SPI_FREQUENCY_8M

// Available sensors
#define SENSI_BOARD_ENVIRONMENTAL_BME280_PRESENT   1
#define SENSI_BOARD_ENVIRONMENTAL_MCU_PRESENT      1
#define SENSI_BOARD_ACCELEROMETER_LIS2DH12_PRESENT 0

// Radio definitions
#define SENSI_BOARD_BLE_MANUFACTURER_ID 0x0499 // Sensi Innovations
#define SENSI_BOARD_TX_POWER_0 -40
#define SENSI_BOARD_TX_POWER_1 -30
#define SENSI_BOARD_TX_POWER_2 -20
#define SENSI_BOARD_TX_POWER_3 -12
#define SENSI_BOARD_TX_POWER_4 -8
#define SENSI_BOARD_TX_POWER_5 -4
#define SENSI_BOARD_TX_POWER_6 -0
#define SENSI_BOARD_TX_POWER_7  4
#define SENSI_BOARD_TX_POWER_LIST { SENSI_BOARD_TX_POWER_0 \\
                                    SENSI_BOARD_TX_POWER_1 \\
                                    SENSI_BOARD_TX_POWER_2 \\
                                    SENSI_BOARD_TX_POWER_3 \\
                                    SENSI_BOARD_TX_POWER_4 \\
                                    SENSI_BOARD_TX_POWER_5 \\
                                    SENSI_BOARD_TX_POWER_6 \\
                                    SENSI_BOARD_TX_POWER_7 \\}
#define SENSI_BOARD_TX_POWER_MIN SENSI_BOARD_TX_POWER_0
#define SENSI_BOARD_TX_POWER_MAX SENSI_BOARD_TX_POWER_7

#endif