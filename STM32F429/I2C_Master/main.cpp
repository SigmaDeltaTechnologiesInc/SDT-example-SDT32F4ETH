/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define SLAVE_ADDRESS   (0x50 << 1)     // 0xA0
I2C i2c(MBED_CONF_APP_L152_I2C_SDA, MBED_CONF_APP_L152_I2C_SCL);

int main()
{
    printf("I2C Master...\n");

    char data_address[1] = {0x00};
    char size_data = 7;     // "Slave1" or "Slave2"
    char data[size_data] = {0,};

    while (1)
    {
        /* To receive a message "Slave1" */
        thread_sleep_for(5000);

        data_address[0] = 0x01;
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

        /* To receive a message "Slave2" */
        thread_sleep_for(5000);

        data_address[0] = 0x02;
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
