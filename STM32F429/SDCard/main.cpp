/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "SDBlockDevice.h"

SDBlockDevice sd(MBED_CONF_APP_SDCARD_SPI_MOSI, MBED_CONF_APP_SDCARD_SPI_MISO, MBED_CONF_APP_SDCARD_SPI_SCK, MBED_CONF_APP_SDCARD_SPI_SS0);
uint8_t block[512] = "Hello World!\n";

int main()
{
    printf("SD Card\n");

    // Call the SDBlockDevice instance initialisation method
    int ret = sd.init();
    if (0 != ret)
    {
        printf("Init failed. %d\n", ret);
        return -1;
    }
    printf("sd size: %llu\n", sd.size());
    printf("sd read size: %llu\n", sd.get_read_size());
    printf("sd program size: %llu\n", sd.get_program_size());
    printf("sd erase size: %llu\n", sd.get_erase_size());

    // Set the frequency
    if (0 != sd.frequency(5000000))
    {
        printf("Error setting frequency \n");
    }

    if (0 != sd.erase(0, sd.get_erase_size()))
    {
        printf("Error Erasing block \n");
    }

    // Write data block to the device
    if (0 == sd.program(block, 0, 512))
    {
        // Read the data block from the device
        if (0 == sd.read(block, 0, 512))
        {
            // Print the contents of the block
            printf("%s", block);
        }
    }

    // Call the SDBlockDevice instance de-initialisation method
    sd.deinit();
}
