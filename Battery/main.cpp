/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE       1000
#define PORT_LED            PA_11
#define PORT_BATTERY        PA_12


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(PORT_LED);
    AnalogIn bat(PORT_BATTERY);

    while (true) {
        led = !led;
        printf("Toggle\n");
        printf("percentage: %3.3f%%\n", bat.read() * 100.0f);
        printf("normalized: 0x%04X \n", bat.read_u16());
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
