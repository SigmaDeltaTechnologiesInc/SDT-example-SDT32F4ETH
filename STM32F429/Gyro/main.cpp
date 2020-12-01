/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "LSM6DS3.h"

SPI spi(MBED_CONF_APP_GYRO_SPI_MOSI, MBED_CONF_APP_GYRO_SPI_MISO, MBED_CONF_APP_GYRO_SPI_SCK); // mosi, miso, sclk
DigitalOut cs(MBED_CONF_APP_GYRO_SPI_SS0, 0);

LSM6DS3 gyro(SPI_MODE, &spi, &cs);

int main()
{
    printf("Hi, Gyro! \r\n");

    int16_t gyro_raw_x = 0;
    int16_t gyro_raw_y = 0;
    int16_t gyro_raw_z = 0;

    status_t ret = gyro.begin();
    printf("ret : %d\n", ret);
    
    while (1)
    {
        thread_sleep_for(5000);

        gyro_raw_x = gyro.readRawGyroX();
        gyro_raw_y = gyro.readRawGyroY();
        gyro_raw_z = gyro.readRawGyroZ();

        printf("gyro_raw_x : %d\n", gyro_raw_x);
        printf("gyro_raw_y : %d\n", gyro_raw_y);
        printf("gyro_raw_z : %d\n", gyro_raw_z);
        printf("\n");
    }
}
