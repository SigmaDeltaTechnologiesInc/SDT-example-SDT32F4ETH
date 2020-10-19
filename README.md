# SDT32F4ETH Examples
Getting Started
===============


Pre-Requisites
--------------

To build these examples, you need to have a computer with software installed as described [here](https://os.mbed.com/docs/latest/tools/index.html).

* DAP Station V2.0
* SDT_IN103_V0.1
* SDT_32F4_SOM_V2.0 with SDT_SOM_DEBUG_V0.1


Targets for compile
---------------

The following targets have been tested and work with these examples:

* ST:
	* NUCLEO_F429ZI


Building and testing the examples
---------------------------------

__To build an example:__

1. Clone the repository containing the collection of examples:

	```
	$ git clone https://github.com/SigmaDeltaTechnologiesInc/SDT-example-SDT32F4ETH.git
	```

1. Using a command-line tool, navigate to any of the example directories, like BLE_Button:

	```
	$ cd SDT-example-SDT32F4ETH
	$ cd WiFi
	```

1. Update the source tree:

	```
	mbed deploy
	```

1. Run the build:

	```
    mbed compile -t GCC_ARM -m NUCLEO_F429ZI
    ```

__To run the application on your board:__

1. Connect your mbed board to your computer over USB. It appears as removable storage.

1. When you run the `mbed compile -t GCC_ARM -m NUCLEO_F429ZI` command above, mbed cli creates a .bin or a .hex file (depending on your target) in ```BUILD/<target-name>/<toolchain>``` under the example's directory. Drag and drop the file to the removable storage.
