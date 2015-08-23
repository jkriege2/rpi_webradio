#! /bin/bash

apt-get update
apt-get install g++-4.8 gcc-4.8
update-alternatives --remove-all gcc 
update-alternatives --remove-all g++
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 20
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.6 20
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
apt-get install libpixman-1-dev libcairo2 libcairo2-dev