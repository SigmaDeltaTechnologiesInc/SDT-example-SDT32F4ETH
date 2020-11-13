/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define SPI_MODE 0

/*  You need to modify a part of PeripheralPins.c for using PC_5 as SPI_SS0
    Path: mbed-os/targets/TARGET_STM/TARGET_STM32L1/TARGET_NUCLEO_L152RE/PeripheralPins.c
    
    MBED_WEAK const PinMap PinMap_SPI_SSEL[] = {
        {PA_4,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)},
        {PA_4_ALT0,  SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)},
        {PA_15,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)},
        {PA_15_ALT0, SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)},
        {PB_12,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)},
        {PC_5,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)},
        {NC, NC, 0}
    };
*/

SPISlave device(MBED_CONF_APP_F429_SPI_MOSI, MBED_CONF_APP_F429_SPI_MISO, MBED_CONF_APP_F429_SPI_SCK, MBED_CONF_APP_F429_SPI_SS0); // mosi, miso, sclk, ssel

int main()
{
    printf("Hi, Slave! \r\n");

    // Setup the spi for 8 bit data, high steady state clock,
    // second edge capture, with a 1MHz clock rate
    device.format(8, SPI_MODE);
    device.frequency(1000000);

    int send_byte = 0xB0;
    int receive_byte = 0;

    device.reply(send_byte); // Full duplex to read first

    // TODO: change to GPIO handler
    while (1)
    {
        if (device.receive())
        {
            receive_byte = device.read(); // Read byte from master

            printf("Slave send : 0x%X\r\n", send_byte);
            printf("Slave received: 0x%X\r\n", receive_byte);

            send_byte++;
            device.reply(send_byte);
        }
    }
}
