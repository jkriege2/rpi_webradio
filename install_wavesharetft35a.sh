#! /bin/bash

sudo apt-get install git
git clone https://github.com/swkim01/waveshare-dtoverlays.git
sudo cp waveshare-dtoverlays/*.dtb /boot/overlays/
sudo echo "dtparam=i2c_arm=on\ndtparam=i2s=on\ndtparam=spi=on\n\ndtoverlay=waveshare35a:rotate=180" >> /boot/config.txt
wget https://github.com/jkriege2/rpi_webradio/raw/master/images/logo1_480.png
sudo fbi -d /dev/fb1 -T 1 -noverbose -a logo1_480.png