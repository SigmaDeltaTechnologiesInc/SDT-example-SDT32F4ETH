# SDT32F4ETH Examples
Getting Started
===============


Pre-Requisites
--------------

To build these examples, you need to have a computer with software installed as described [here](https://os.mbed.com/docs/latest/tools/index.html).

* H/W 
	* DAP Station V2.0
	* SDT_IN103_V0.1
	* SDT_32F4_SOM_V2.0 with SDT_SOM_DEBUG_V0.1

* S/W
	* Python: 2.7.17
	* GCC_ARM(arm-none-eabi-gcc): 9.2.1
	* Mercurial: 4.5.3
	* mbed cli: 1.10.2
	* mbed serial driver


Targets for compile
--------------------

The following targets have been tested and work with these examples:

* BLE:
	* SDT52832B
* Other:
	* NUCLEO_F429ZI
	* SDT32F4ETH


Examples
--------

STM32F429
Functions		| H/W Ver.01	| H/W Ver.02	| Notes
----------------|---------------|---------------|---------------
Audio			|Confirmed		|Not confirmed	|Codec IC changed
AWS				|Confirmed		|Confirmed		|
Battery			|Confirmed		|Confirmed		|
BLE				|Confirmed		|Confirmed		|
EEPROM			|Confirmed		|Confirmed		|
GPIO			|Confirmed		|Confirmed		|
GPS				|Confirmed		|Confirmed		|
Gyro			|Confirmed		|Confirmed		|
I2C_Master		|Confirmed		|Not supported	|
LCD				|Not supported	|Confirmed		|
LTE				|Confirmed		|Confirmed		|
SDCard			|Confirmed		|Not supported	|
UART_Master		|Confirmed		|Confirmed		|
WiFi			|Confirmed		|Confirmed		|

STM32L152
Functions		| H/W Ver.01	| H/W Ver.02	| Notes
----------------|---------------|---------------|---------------
GPIO			|Confirmed		|Confirmed		|
I2C_Slave		|Confirmed		|Not supported	|
SPI_Slave		|Confirmed		|Not supported	|
UART_Slave		|Confirmed		|Confirmed		|

SDT52832B
Functions		| H/W Ver.01	| H/W Ver.02	| Notes
----------------|---------------|---------------|---------------
BLE				|Confirmed		|Confirmed		|


Building and testing the examples
---------------------------------

__To build an example:__

1. Clone the repository containing the collection of examples:

	```
	$ git clone https://github.com/SigmaDeltaTechnologiesInc/SDT-example-SDT32F4ETH
	```

1. Using a command-line tool, navigate to any of the example directories:

	```
	$ cd SDT-example-SDT32F4ETH
	$ cd STM32F429
	$ cd GPIO
	```

1. Update the source tree (For each directory, only once at the first time):

	```
	mbed deploy
	```

1. Run the build (Every time your code is modified):
	- If NUCLEO_F429ZI,
	```
    mbed compile -t GCC_ARM -m NUCLEO_F429ZI
    ```
	- If NUCLEO_L152RE,
	```
    mbed compile -t GCC_ARM -m NUCLEO_L152RE
    ```
	- If SDT52832B,
	```
    mbed compile -t GCC_ARM -m SDT52832B
    ```

__To do list before building your code:__

1. When you make application of STM32L152 as SPI Slave, you have to modify a file(PeripheralPins.c) as below.
	```
	/* Path: mbed-os/targets/TARGET_STM/TARGET_STM32L1/TARGET_NUCLEO_L152RE/PeripheralPins.c */
	[snip]
	MBED_WEAK const PinMap PinMap_SPI_SSEL[] = {
        {PA_4,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)},
        {PA_4_ALT0,  SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)},
        {PA_15,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)},
        {PA_15_ALT0, SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)},
        {PB_12,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)},
        {PC_5,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)},
        {NC, NC, 0}
    };
	```

__To run the application on your board:__

1. Connect your mbed board to your computer over USB. It appears as removable storage.

1. When you run the `mbed compile -t GCC_ARM -m NUCLEO_F429ZI` command above, mbed cli creates a .bin or a .hex file (depending on your target) in ```BUILD/<target-name>/<toolchain>``` under the example's directory. Drag and drop the file to the removable storage.


Mbed OS version
---------------

* mbed-os 6.3.0 [here](https://github.com/ARMmbed/mbed-os/#0db72d0cf26539016efbe38f80d6f2cb7a3d4414)


Reference API on Mbed OS 6.3.0
-------------------------------

Please refer to [here](https://os.mbed.com/docs/mbed-os/v6.3/apis/index.html)
