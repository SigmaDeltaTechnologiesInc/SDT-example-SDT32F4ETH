/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define SPI_MODE 0

SPI spi(MBED_CONF_APP_GYRO_SPI_MOSI, MBED_CONF_APP_GYRO_SPI_MISO, MBED_CONF_APP_GYRO_SPI_SCK); // mosi, miso, sclk
DigitalOut cs(MBED_CONF_APP_GYRO_SPI_SS0);

int main()
{
    printf("Hi, Master! \r\n");

    // Chip must be deselected
    cs = 1;
    thread_sleep_for(1000);

    // Setup the spi for 8 bit data, high steady state clock,
    // second edge capture, with a 1MHz clock rate
    spi.format(8, SPI_MODE);
    spi.frequency(1000000);

    int send_byte = 0xA0;
    int receive_byte = 0;

    while (1)
    {
        thread_sleep_for(5000);

        // Select the device by seting chip select low
        cs = 0;

        // Send a byte to receive the data in full duplex mode.
        receive_byte = spi.write(send_byte);

        // Deselect the device
        cs = 1;

        printf("Master send : 0x%X\r\n", send_byte);
        printf("Master received: 0x%X\r\n", receive_byte);

        send_byte++;
    }
}
