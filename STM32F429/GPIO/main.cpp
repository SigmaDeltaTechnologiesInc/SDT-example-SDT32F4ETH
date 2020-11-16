/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE       5000
#define PORT_GPIO           PA_11

DigitalOut led(PORT_GPIO);

DigitalOut gpio10(MBED_CONF_APP_GPIO10);
DigitalOut gpio11(MBED_CONF_APP_GPIO11);
DigitalOut gpio12(MBED_CONF_APP_GPIO12);
DigitalOut gpio13(MBED_CONF_APP_GPIO13);
DigitalOut gpio14(MBED_CONF_APP_GPIO14);
DigitalOut gpio15(MBED_CONF_APP_GPIO15);
DigitalOut gpio16(MBED_CONF_APP_GPIO16);
DigitalOut gpio17(MBED_CONF_APP_GPIO17);
DigitalOut gpio18(MBED_CONF_APP_GPIO18);

void test_gpio(void)
{
    gpio10 = !gpio10;
    gpio11 = !gpio11;
    gpio12 = !gpio12;
    gpio13 = !gpio13;
    gpio14 = !gpio14;
    gpio15 = !gpio15;
    gpio16 = !gpio16;
    gpio17 = !gpio17;
    gpio18 = !gpio18;
    
    printf("gpio10: %d\n", gpio10.read());
    printf("gpio11: %d\n", gpio11.read());
    printf("gpio12: %d\n", gpio12.read());
    printf("gpio13: %d\n", gpio13.read());
    printf("gpio14: %d\n", gpio14.read());
    printf("gpio15: %d\n", gpio15.read());
    printf("gpio16: %d\n", gpio16.read());
    printf("gpio17: %d\n", gpio17.read());
    printf("gpio18: %d\n", gpio18.read());
}

int main()
{
    while (true) {
        led = !led;
        test_gpio();
        printf("Toggle\n");
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
