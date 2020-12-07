/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define BLINKING_RATE           5000
#define DEFAULT_SLAVE_ADDRESS   (0x70 << 1)

typedef enum
{
    REG_MODE                    = 0x00,
    REG_CTRL,
    REG_CHARGE_LOW,
    REG_CHARGE_HIGH,
    REG_COUNTER_LOW,
    REG_COUNTER_HIGH,
    REG_CURRENT_LOW,
    REG_CURRENT_HIGH,
    REG_VOLTAGE_LOW,
    REG_VOLTAGE_HIGH,
    REG_TEMPERATURE_LOW,
    REG_TEMPERATURE_HIGH,
    REG_CONTROL_MAX,
} REGISTER_CONTROL;

typedef enum
{
    REG_ID0                     = 0x18,
    REG_ID1,
    REG_ID2,
    REG_ID3,
    REG_ID4,
    REG_ID5,
    REG_ID6,
    REG_ID7,
    REG_DEVICE_ID_MAX,
} REGISTER_DEVICE_ID;

I2C* bat = NULL;

char get_data(char address)
{
    if (bat != NULL)
    {
        if (bat->write(DEFAULT_SLAVE_ADDRESS, &address, 1))
        {
            printf("Fail to send I2C write CMD\n");
        }
        else
        {
            char data[1];
            if (bat->read(DEFAULT_SLAVE_ADDRESS, data, 1))
            {
                printf("Fail to send I2C read CMD\n");
            }
            else
            {
                // printf("data: 0x%02X\n", data[0]);
                return data[0];
            }
        }
    }

    printf("Fail\n");

    return -1;
}

int main()
{
    printf("Battery\n");

    bat = new I2C(MBED_CONF_APP_BATTERY_I2C_SDA, MBED_CONF_APP_BATTERY_I2C_SCL);

    uint8_t data_temp = 0;
    uint8_t voltage_low = 0;
    uint8_t voltage_high = 0;
    uint16_t voltage = 0;

    char cmd[2];
    cmd[0] = REG_MODE;
    cmd[1] = 0x10;      // GG_RUN -> 0: standby mode, 1: operating mode
    bat->write(DEFAULT_SLAVE_ADDRESS, cmd, 2);
    ThisThread::sleep_for(4000);

    while (true)
    {
        for (size_t i = REG_MODE; i < REG_CONTROL_MAX; i++)
        {
            data_temp = get_data(i);
            printf("data[%d]: 0x%02X\n", i, data_temp);
            ThisThread::sleep_for(100);

            if (i == REG_VOLTAGE_LOW)
            {
                voltage_low = data_temp;
            }
            if (i == REG_VOLTAGE_HIGH)
            {
                voltage_high = data_temp;
            }
        }
        printf("\n");

        for (size_t i = REG_ID0; i < REG_DEVICE_ID_MAX; i++)
        {
            data_temp = get_data(i);
            printf("data[%d]: 0x%02X\n", i, data_temp);
            ThisThread::sleep_for(100);
        }
        printf("\n");

        voltage = ((uint16_t)voltage_high << 8) | (voltage_low);
        printf("voltage: 0x%04X (%.0f mV)\n", voltage, (float)voltage * 2.44);
        printf("\n");
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
