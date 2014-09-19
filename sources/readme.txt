-- To build the kernel, make sure Xilinx Linux cross compiler is installed and
   environment variable is pointing to it. In particular, be sure environmental
   variable CROSS_COMPILE is set and PATH includes the CodeBench tools.
   For details, please refer to http://wiki.xilinx.com/zynq-tools

1) Get Xilinx Linux kernel tagged "xilinx-14.1-build3-trd"
   GIT:
   bash> git clone git://git.xilinx.com/linux-xlnx.git
   bash> git checkout xilinx-14.1-build3-trd

2) Goto Linux kernel directory "linux-xlnx", and copy xylonfb patch there.
   Xylonfb patch creates latest frame buffer driver version with ADV7511 driver
   and FPGA pixel clock driver.
   Additonally xylonfb patch creates in "linux-xlnx" folder kernel configuration
   .config file and proper devicetree.dts file.
   After applying the patch, kernel has its configuration file and it is ready
   for compiling (building).
   bash> cd linux-xlnx
   bash> patch -p1 < patch_xylonfb_$DATE

3) Build the kernel
   bash> make ARCH=arm

   - After kernel build procedure is finished,
     kernel zImage can be found in arch/arm/boot/zImage
   - Created zImage file is copied to SD card root and used by kernel

4) Compile the devicetree configuration file.
   Compiled devicetree.dtb file for HDMI design is included in SD image.

   - devicetree.dts is located in "linux-xlnx" kernel folder.
   - devicetree.dts is located in Xylon installation /software/dts/ folder.
   - to compile devicetree configuration (.dts) file manually, file must be
     copied into "linux-xlnx" kernel folder, or correct path preceeding .dts
     file must be stated

   Compiling devicetree.dts configuration file for HDMI design:
   - position to "linux-xlnx" kernel folder
   bash> ./scripts/dtc/dtc -I dts -O dtb -o devicetree.dtb devicetree.dts
   - Created devicetree.dtb file is copied to SD card root and used by kernel




OPTIONAL:

*) Configuring the Linux kernel with Xilinx Zynq configuration
   bash> make ARCH=arm xilinx_zynq_defconfig

*) Configuring the Linux kernel
   bash> make ARCH=arm menuconfig

*) Configuring Xylon frame buffer driver
   bash> make ARCH=arm menuconfig
    In graphic menu position to:
    Device Drivers -> Graphics support -> Support for frame buffer devices ->
    Xylon logiCVC frame buffer support
     Xylon frame buffer driver type :: Platform driver (kernel default)
                                    :: OF driver
     Xylon logiCVC pixel clock source :: External pixel clock
                                      :: Zynq PS pixel clock (kernel default)
                                      :: ZC702 board pixel clock
                                      :: Xylon clkgen pixel clock
   IMPORTANT NOTE!
   For Xylon ZGPU and ZHMI-FMC reference designs
   -> Xylon frame buffer driver type must be set to "OF driver"
   -> Xylon logiCVC pixel clock source must be set to "Xylon clkgen pixel clock"
   -> Device Drivers -> Misc devices -> "Analog Devices AV7511 HDMI transmitter" must be selected

*) Ramdisk filesystem module information
   To get proper kernel drivers module insertion/removing, ramdisk filesystem
   must contain kernel module information. This is achieved by installing kernel
   module information and available modules into the ramdisk filesystem
   provided by Xilinx. Xilinx gzip-ed filesystem is called "ramdisk8M.image.gz"
   and it must be available to the Linux kernel on SD card.

   Instructions for installing kernel modules into the ramdisk filesystem on
   host machine:
   - "ramdisk8M.image.gz" must be available in "linux-xlnx" kernel folder
   1. position to "linux-xlnx" kernel folder
   2. sudo mkdir /mnt/ramdisk
   3. gunzip ramdisk8M.image.gz
   4. sudo mount -o loop ramdisk8M.image /mnt/ramdisk/
   5. sudo rm -r /mnt/ramdisk/lib/modules/
   6. sudo make ARCH=arm INSTALL_MOD_PATH=/mnt/ramdisk modules_install
   7. sudo umount /mnt/ramdisk/
   8. gzip -9 ramdisk8M.image
   - copy created "ramdisk8M.image.gz" to SD card root
