/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define BLINKING_RATE   1000

#define UART_BAUDRATE   115200
UnbufferedSerial pc(PC_12, PD_2, UART_BAUDRATE);
UnbufferedSerial uart(MBED_CONF_APP_BT_UART_TX, MBED_CONF_APP_BT_UART_RX, UART_BAUDRATE);

char data_rx = 0;

void callback_rx(void)
{
    // You can not call 'printf' function in callback function.
    while (uart.readable())
    {
        uart.read(&data_rx, 1);
        pc.write(&data_rx, 1);
    }
}

int main()
{
    printf("BLE\n");

    printf("It will display the message from the BLE mcu\n");
    uart.attach(callback_rx, SerialBase::RxIrq);

    while (true)
    {
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
