/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define BLINKING_RATE   1000

#define UART_BAUDRATE   115200
RawSerial pc(PC_12, PD_2, UART_BAUDRATE);
RawSerial uart(MBED_CONF_APP_F429_UART_TX, MBED_CONF_APP_F429_UART_RX, UART_BAUDRATE);

char data_rx = 0;
char data_end = 'a';

void callback_rx(void)
{
    // You can not call 'printf' function in callback function.
    while (uart.readable())
    {
        data_rx = uart.getc();
        pc.putc(data_rx);
        if (data_rx == '\0')
        {
            pc.putc('\n');
            uart.putc(data_end);
        }
    }
}

int main()
{
    pc.printf("UART L152\n");

    uart.attach(callback_rx, Serial::RxIrq);

    while (true)
    {
        ThisThread::sleep_for(10);
    }
}
