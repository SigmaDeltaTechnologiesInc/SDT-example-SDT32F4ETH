/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE       5000
#define PORT_GPIO           PA_11

DigitalOut led(PORT_GPIO);

DigitalOut gpio20(MBED_CONF_APP_GPIO20);

void test_gpio(void)
{
    gpio20 = !gpio20;
    
    printf("gpio20: %d\n", gpio20.read());
}

int main()
{
    printf("GPIO\n");

    while (true) {
        led = !led;
        test_gpio();
        printf("\n");
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
