/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define BLINKING_RATE   5000

AnalogIn kg_break(MBED_CONF_APP_KICKGOING_BREAK);
AnalogIn kg_throttle(MBED_CONF_APP_KICKGOING_THROTTLE);
DigitalOut kg_front_led_on(MBED_CONF_APP_KICKGOING_FRONT_LED, 1);
PwmOut kg_bar_led(MBED_CONF_APP_KICKGOING_BAR_LED);

void test_analogin(void)
{
    printf("kg_break: %3.2f%%\n", kg_break.read() * 100.0f);
    printf("kg_break: 0x%04X\n", kg_break.read_u16());
    
    printf("kg_throttle: %3.2f%%\n", kg_throttle.read() * 100.0f);
    printf("kg_throttle: 0x%04X\n", kg_throttle.read_u16());
}

void test_digitalout(void)
{
    kg_front_led_on = !kg_front_led_on;
    printf("kg_front_led_on: %d\n", kg_front_led_on.read());
}

void test_pwmout(float period, float duty)
{
    printf("kg_bar_led: period %.2f sec, duty %3.2f %%\n", period, duty);
    kg_bar_led.period(period);
    kg_bar_led.write(duty);
}

int main()
{
    printf("GPIO\n");

    test_pwmout(2.0f, 0.30f);   // 2 sec, 30% duty cycle

    while (true)
    {
        ThisThread::sleep_for(BLINKING_RATE);

        test_analogin();
        test_digitalout();
    }
}
