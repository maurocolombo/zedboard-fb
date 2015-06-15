Per avviare l'immagine dall'u-boot fare:

setenv bootargs "console=ttyPS0,115200 root=/dev/mmcblk0p2 rw earlyprintk rootwait"
fatload mmc 0 0x3000000 uImage
fatload mmc 0 0x2A00000 devicetree.dtb
bootm 0x3000000 - 0x2A00000

files scaricati da: http://www.logicbricks.com/logicBRICKS/Reference-logicBRICKS-Design/Xylon-Reference-Designs-Navigation-Page.aspx
Zynq-7000 AP SoC Designs for the ZedBoard™ -> logiREF-ZGPU-ZED Graphics Processing Unit (April 24, 2015) - Design description (NEW!) -> Download JAR Installer
