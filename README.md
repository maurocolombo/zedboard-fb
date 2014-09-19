zedboard-fb
===========
Utilizzato l'SDK 1.1.0, il pacchetto da cui sono state tratte le info è ZGPU-ZED_120919
source /home/architech/architech_sdk/architech/zedboard/toolchain/environment-nofs
git clone git://git.xilinx.com/linux-xlnx.git
cd linux-xlnx
git checkout xilinx-14.1-build3-trd
cd ..
patch -p1 -d linux-xlnx/ < /path/to/patch_xylonfb_20120919
cd linux-xlnx
make ARCH=arm
cp devicetree.dtb linux-xlnx/arch/arm/boot/dts
# editare active-layer = <0>; per selezionare la modalità, vedi xylonfb-platform.c riga 85
./scripts/dtc/dtc -I dts -O dtb -o devicetree.dtb arch/arm/boot/dts/devicetree.dts

!!! vedi readme.txt e xylon-linux-framebuffer.pdf per dettagli !!!

Come rootfs è stato usato le qt4demo

i comandi dell'u-boot sono:
mmcinfo
fatload mmc 0 0x8000 zImage
fatload mmc 0 0x1000000 devicetree.dtb
go 0x8000


fb.c crea un file da visualizzare direttamente sul frame buffer.
	fb [num byte depth] [ byte1] [byte2] ... [byteN] [len]
	es. fb 2 5 10 20 - crea 20 coppie di byte 5,10
	
per le qtquick le opengl es1.1 non vanno bene: http://qt-project.org/forums/viewthread/26590

