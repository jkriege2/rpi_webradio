#! /bin/bash

curl -SLs https://apt.adafruit.com/add | bash
sudo apt-get install raspberrypi-bootloader
sudo apt-get install adafruit-pitft-helper
sudo adafruit-pitft-helper -t 22

sudo echo "fbtft_device name=adafruit22a" >> /etc/modules