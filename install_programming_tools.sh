#! /bin/bash


apt-get update

# install development tools
apt-get install g++-4.8 gcc-4.8
update-alternatives --remove-all gcc 
update-alternatives --remove-all g++
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 20
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.6 20
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50

#install cairo etc.
apt-get install libpixman-1-dev libcairo2 libcairo2-dev

# install alsa
sudo apt-get install alsa-base alsa-utils

# install mpd, libmpdcleint, mpc
apt-get install mpd mpc libmpdclient2

# activate sound drivers for ES9023, see e.g. http://www.linuxmediaserver.net/howto/openelec-es9023-using-i2s/
echo "\nsnd_soc_bcm2708\nsnd_soc_bcm2708_i2s\nbcm2708_dmaengine\nsnd_soc_pcm5102a\nsnd_soc_hifiberry_dac\n" >> /etc/modules

# clone and install wiringPi
git clone git://git.drogon.net/wiringPi
cd wiringPi
./build
cd ..
