/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE       1000
#define PORT_LED            PA_11   // F429에는 LED 없음


int main()
{
    // Initialise the digital pin LED1 as an output
    // DigitalOut led(PORT_LED);

    while (true) {
        // led = !led;
        printf("Toggle\n");
        ThisThread::sleep_for(BLINKING_RATE);
    }
}