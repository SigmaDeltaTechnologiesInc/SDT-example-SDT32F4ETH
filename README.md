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


Examples
--------

* AWS: Confirmed on board
* Battery: Not confirmed on board
* BLE: Not confirmed on board
* GPS: Not confirmed on board
* LED: Not confirmed on board
* LTE: Not confirmed on board
* WiFi: Confirmed on board


Mbed OS version
---------------

* mbed-os 5.15.5 [here](https://github.com/ARMmbed/mbed-os/#6a244d7adffc0e93872cfc880e539ee11bbc6002)


Building and testing the examples
---------------------------------

__To build an example:__

1. Clone the repository containing the collection of examples:

	```
	$ git clone https://github.com/SigmaDeltaTechnologiesInc/SDT-example-SDT32F4ETH
	```

1. Using a command-line tool, navigate to any of the example directories, like WiFi:

	```
	$ cd SDT-example-SDT32F4ETH
	$ cd WiFi
	```

1. Update the source tree (For each directory, only once at the first time):

	```
	mbed deploy
	```

1. Run the build (Every time your code is modified):

	```
    mbed compile -t GCC_ARM -m NUCLEO_F429ZI
    ```

__To run the application on your board:__

1. Connect your mbed board to your computer over USB. It appears as removable storage.

1. When you run the `mbed compile -t GCC_ARM -m NUCLEO_F429ZI` command above, mbed cli creates a .bin or a .hex file (depending on your target) in ```BUILD/<target-name>/<toolchain>``` under the example's directory. Drag and drop the file to the removable storage.


Reference API on Mbed OS 5.15.5
-------------------------------

Please refer to [here]https://os.mbed.com/docs/mbed-os/v5.15/apis/index.html
