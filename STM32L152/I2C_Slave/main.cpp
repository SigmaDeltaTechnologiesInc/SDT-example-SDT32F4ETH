/* mbed Microcontroller Library
Copyright (c) 2019 ARM Limited
SPDX-License-Identifier: Apache-2.0
 */

#include <mbed.h>

#if !DEVICE_I2CSLAVE
#error[NOT_SUPPORTED] I2C Slave is not supported
#endif

#define SLAVE_ADDRESS (0x50 << 1)
I2CSlave slave(MBED_CONF_APP_F429_I2C_SDA, MBED_CONF_APP_F429_I2C_SCL);

#if 1
int main()
{
    printf("I2C Slave...\n");
    char buf[10];
    char data_address = 0x00;
    char msg1[7] = "Slave1";
    char msg2[7] = "Slave2";

    slave.address(SLAVE_ADDRESS);

    while (1)
    {
        int i = slave.receive();

        switch (i)
        {
        case I2CSlave::ReadAddressed:
            switch (data_address)
            {
            case 0x01:
                slave.write(msg1, sizeof(msg1));
                printf("Write message1: %s\n", msg1);
                break;
            case 0x02:
                slave.write(msg2, sizeof(msg2));
                printf("Write message2: %s\n", msg2);
                break;
            default:
                break;
            }
            break;
        case I2CSlave::WriteGeneral:
            slave.read(buf, 1);
            printf("Read G: %d\n", buf);
            break;
        case I2CSlave::WriteAddressed:
            slave.read(buf, 1);
            printf("Read A: 0x%02X\n", buf[0]);
            data_address = buf[0];
            for (int i = 0; i < 10; i++)
            {
                buf[i] = 0; // Clear buffer
            }
            break;
        }
    }
}

#else

int main()
{
    printf("I2C Slave...\n");
    char buf[10];
    char msg[] = "Slave!";

    slave.address(SLAVE_ADDRESS);

    int byte_read = 0;

    while (1)
    {
        thread_sleep_for(10);
        int operation = slave.receive();
        switch (operation)
        {
        case I2CSlave::ReadAddressed:
        {
            int status = slave.write(msg, sizeof(msg));
            if (status == 0)
            {
                printf("Written msg: %s\n", msg);
            }
            else
            {
                printf("Failed to write msg.\n");
            }
            break;
        }
        case I2CSlave::WriteGeneral:
            byte_read = slave.read();
            printf("Read General: %c (%d)\n", byte_read, byte_read);
            break;
        case I2CSlave::WriteAddressed:
            byte_read = slave.read();
            printf("Read Addressed: %c (%d)\n", byte_read, byte_read);
            break;
        }
    }
}
#endif
