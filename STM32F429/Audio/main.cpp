/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

I2C i2c(MBED_CONF_APP_AUDIO_I2C_SDA, MBED_CONF_APP_AUDIO_I2C_SCL);

#define AUDIO_STABLE_TIME_SEC           10
#define SLAVE_ADDRESS                   (0x12 << 1)
#define DATA_ADDRESS                    (0x04)          // SIGNAL_SELECT_3

int main()
{
    printf("I2C Master...\n");

    char data_address[1] = {0x00};
    char size_data = 1;     // "Slave1" or "Slave2"
    char data[size_data + 1] = {0,};

    while (1)
    {
        /* To receive a message "Slave1" */
        thread_sleep_for(1000 * AUDIO_STABLE_TIME_SEC);

        printf("Read a data address(0x%02X)\n", DATA_ADDRESS);
        data_address[0] = DATA_ADDRESS;
        if (i2c.write(SLAVE_ADDRESS, data_address, 1))
        {
            printf("Fail to write\n");
        }
        if (i2c.read(SLAVE_ADDRESS, data, size_data))
        {
            printf("Fail to read\n");
        }

        printf("data = %s\n", data);
        for (int i = 0; i < size_data; i++)
        {
            data[i] = 0; // Clear buffer
        }

        printf("\n");
    }
}
