#! /bin/sh

sudo apt-get install git
git clone https://github.com/waveshare/LCD-show.git
cd LCD-show
chmod +x LCD35-show
sudo ./LCD35-show
sudo ./LCD35-show 270

wget https://github.com/jkriege2/rpi_webradio/raw/master/images/logo1_480.png
sudo fbi -d /dev/fb1 -T 1 -noverbose -a logo1_480.png