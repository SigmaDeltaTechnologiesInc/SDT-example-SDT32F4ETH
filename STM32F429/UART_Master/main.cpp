/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define BLINKING_RATE 5

#define UART_BAUDRATE 115200
RawSerial uart(MBED_CONF_APP_L152_UART_TX, MBED_CONF_APP_L152_UART_RX, UART_BAUDRATE);

char data_tx[] = "Hi L152";
char data_rx = 0;
char data_end = 'a';
bool is_end = false;

void callback_rx(void)
{
    // You can not call 'printf' function in callback function.
    data_rx = uart.getc();
    if (data_rx == data_end)
    {
        is_end = true;
    }
}

void callback_ticker(void)
{
    for (size_t i = 0; i < sizeof(data_tx); i++)
    {
        uart.putc(data_tx[i]);
    }
}

int main()
{
    printf("UART F429\n");

    uart.attach(callback_rx, SerialBase::RxIrq);
    
    printf("Start to sending every %d sec...\"%s\"\n", BLINKING_RATE, data_tx);
    printf("Please check seial log of L152\n");
    Ticker ticker;
    ticker.attach(callback_ticker, BLINKING_RATE);

    while (true)
    {
        if (is_end == true)
        {
            is_end = false;
            printf("Success to sending\n");
        }
    }
}
