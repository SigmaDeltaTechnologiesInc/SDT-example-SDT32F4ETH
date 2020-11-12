/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE       1000
#define PORT_GPIO           PA_11


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(PORT_GPIO);

    while (true) {
        led = !led;
        printf("Toggle\n");
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
