/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define BLINKING_RATE           5000
#define DEFAULT_SLAVE_ADDRESS   (0x70 << 1)
#define REG_VOLTAGE_LOW         0x08
#define REG_VOLTAGE_HIGH        0x09

int main()
{
    printf("Battery\n");

    I2C* bat;
    bat = new I2C(MBED_CONF_APP_BATTERY_I2C_SDA, MBED_CONF_APP_BATTERY_I2C_SCL);

    uint8_t address = DEFAULT_SLAVE_ADDRESS;
    char cmd[2];
    char data[1];

    uint8_t voltage_low = 0;
    uint8_t voltage_high = 0;
    uint16_t voltage = 0;

    while (true)
    {
        cmd[0] = REG_VOLTAGE_LOW;
        if (bat->write(address, cmd, 1))
        {
            printf("Fail to send I2C write CMD\n");
        }
        else
        {
            if (bat->read(address, data, 1))
            {
                printf("Fail to send I2C read CMD\n");
            }
            else
            {
                voltage_low = data[0];
                printf("voltage_low: 0x%02X\n", voltage_low);
            }
        }

        ThisThread::sleep_for(1000);

        cmd[0] = REG_VOLTAGE_HIGH;
        if (bat->write(address, cmd, 1))
        {
            printf("Fail to send I2C write CMD\n");
        }
        else
        {
            if (bat->read(address, data, 1))
            {
                printf("Fail to send I2C read CMD\n");
            }
            else
            {
                voltage_high = data[0];
                printf("voltage_high: 0x%02X\n", voltage_high);
            }
        }

        voltage = (voltage_high << 8) | (voltage_low);
        printf("voltage: 0x%04X\n", voltage);
        printf("\n");

        ThisThread::sleep_for(BLINKING_RATE);
    }
}
