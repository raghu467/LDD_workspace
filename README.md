# Linux_Device_Drivers
Hardware platform: Beagle bone black 

#initial host setup
platform: 18.04.1-Ubuntu 

use the following command to install required packages:<br/>
sudo apt-get update <br/>
sudo apt-get install build-essential lzop u-boot-tools net-tools bison flex libssl-dev libncurses5-dev libncursesw5-dev unzip chrpath xz-utils minicom wget git-core<br/>


kernel compilation steps:

STEP 1:<br/>
/*
 *removes all the temporary folder, object files, images generated during the previous build. 
 *This step also deletes the .config file if created previously 
 */
make ARCH=arm distclean<br/>

STEP 2:
/*creates a .config file by using default config file given by the vendor */

make ARCH=arm bb.org_defconfig<br/>


STEP 3:
/*This step is optional. Run this command only if you want to change some kernel settings before compilation */ ​

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig<br/>


STEP 4:
/*Kernel source code compilation. This stage creates a kernel image "uImage" also all the device tree source files will be compiled, and dtbs will be generated */ ​

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- uImage dtbs LOADADDR=0x80008000 -j4<br/>

STEP 5:
/*This step builds and generates in-tree loadable(M) kernel modules(.ko) */

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-  modules  -j4<br/>

STEP 6:
/* This step installs all the generated .ko files in the default path of the computer (/lib/modules/<kernel_ver>) */​<br/>

sudo make ARCH=arm  modules_install
