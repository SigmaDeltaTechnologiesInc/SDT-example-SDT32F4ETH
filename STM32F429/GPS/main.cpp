/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE 1000

Serial gps(MBED_CONF_APP_GPS_UART_TX, MBED_CONF_APP_GPS_UART_RX, 9600);

int main()
{
    char GPS_c;
    char GPS_buffer[512];
    int GPS_i = 0;
    char address_buffer[8];
    int address_i = 0;
    bool address_reading = false;

    printf("\nGPS MESSAGE:\n");

    while (true)
    {
        if (gps.readable())
        {
            GPS_c = gps.getc();

            if (GPS_c == '$' && GPS_i > 0)
            {
                // Check if it is the first gps address (GNGLL)
                if (address_buffer[0] == 'G' && address_buffer[1] == 'N' && address_buffer[2] == 'G' && address_buffer[3] == 'L' && address_buffer[4] == 'L')
                {
                    printf("\nGPS MESSAGE:\n");
                }

                // Print out a single line of gps message
                for (int j = 0; j < GPS_i; j++)
                {
                    printf("%c", (char)GPS_buffer[j]);
                }

                GPS_buffer[0] = GPS_c;
                GPS_i = 1;

                address_i = 0;
                address_reading = true;
            }
            else
            {
                GPS_buffer[GPS_i++] = GPS_c;

                if (address_reading && GPS_c == ',')
                {
                    address_reading = false;
                }
                else if (address_reading)
                {
                    address_buffer[address_i++] = GPS_c;
                }
            }
        }
    }
}
