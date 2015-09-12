#! /bin/bash

echo "INSTALL TOOLS FOR rpi_webradio ON A RASPBERRY-PI:"
echo ""
echo "  -[DEFAULT_MODE]->   run using sudo sh install_programming_tools.sh [username]"
echo "  -[FAST_MODE]->      run using sudo sh install_programming_tools.sh fast [username]"
echo ""
echo ""

CURRENTDIR=${PWD}
USERNAME=pi

FAST="0"
cd `dirname $0`
SCRIPT_DIR=`pwd`
cd $CURRENTDIR
if [ ! -z $1 ] ; then 
  USERNAME=$1
  if [ "$USERNAME" = "fast" ] ; then
      USERNAME=pi
	  FAST="1"
	  if [ ! -z $2 ] ; then 
		USERNAME=$2
	  fi	
  fi
fi

HOMEDIR=/home/$USERNAME

echo "CURRENTDIR = $CURRENTDIR"
echo "USERNAME   = $USERNAME"
echo "HOMEDIR    = $HOMEDIR"
echo "SCRIPT_DIR = $SCRIPT_DIR"
echo "FAST       = $FAST"


if [ "$FAST" = "0" ] ; then
	apt-get update
	apt-get upgrade

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
	
	
	# install samba-client
	apt-get install smb-client

	cd $HOMEDIR
	# clone and install wiringPi
	git clone git://git.drogon.net/wiringPi
	cd wiringPi
	./build
	cd $CURRENTDIR

fi

echo "auto-start mpd [y/n]?"
read AUTOSTART_MPD
if [ "$AUTOSTART_MPD" = "y" ] ; then
	echo "\n# MPD daemon start (if no other user instance exists)\n[ ! -s ~/.config/mpd/pid ] && mpd\n" >> $HOMEDIR/.profile
fi


# activate sound drivers for ES9023 or hifiberry-dac, see e.g. http://www.linuxmediaserver.net/howto/openelec-es9023-using-i2s/
echo "which Audio-hardware do you want to use?"
echo "  - 1: HifiBerry-DAC / ES9023"
echo "  - ENTER: no special hardware/default hardware/USB/... "  
read AUDIOHW
if [ "$AUDIOHW" = "1" ] ; then
	echo "\nsnd_soc_bcm2708\nsnd_soc_bcm2708_i2s\nbcm2708_dmaengine\nsnd_soc_pcm5102a\nsnd_soc_hifiberry_dac\n" >> /etc/modules
	echo "\ndtoverlay=hifiberry-dac\n" >> /boot/config.txt
fi

# make music directory in home
MUSICDIR=$HOMEDIR/music
mkdir -p $MUSICDIR
mkdir -p $MUSICDIR/mpd/playlists
echo "# USERNAME and PASSWORD for NAS-access (if required)\nusername=\npassword=\n" > /etc/samba/mpd.credentials
chown -R $USERNAME /etc/samba/mpd.credentials
sudo chmod 666 /etc/samba/mpd.credentials

chown -R $USERNAME $MUSICDIR
chmod -R 777 $MUSICDIR

echo "Mount network music directory [y/n]?"
read NET_MOUNT
echo  "\n"
if [ "$NET_MOUNT" = "y" ] ; then
    echo "enter path:"  
	read NET_DIR
	echo "enter name for this collection:"  
	read NET_NAME
	mkdir -p /mnt/$NET_NAME
	cd $MUSICDIR
	ln -s /mnt/$NET_NAME
	cd $CURRENTDIR
	echo "\n# mount ${NET_DIR} to /mnt/${NET_NAME}\n${NET_DIR} /mnt/${NET_NAME} cifs auto,rw,uid=mpd,credentials=/etc/samba/mpd.credentials 0 0\n" >> /etc/fstab
	mount -a
fi

echo "Overwrite /etc/mpd.config with customized/taylored version [y/n]?"
read OVERWRITE_MPDCONF
if [ "$OVERWRITE_MPDCONF" = "y" ] ; then
	cp /etc/mpd.conf /etc/mpd.conf.backup
    cp $SCRIPT_DIR/rpi_mpd.conf $SCRIPT_DIR/rpi_mpd.~c
	
	sed "s,%%MUSICDIR%%,$MUSICDIR," $SCRIPT_DIR/rpi_mpd.~c > $SCRIPT_DIR/rpi_mpd.~~c
	cp -f $SCRIPT_DIR/rpi_mpd.~~c $SCRIPT_DIR/rpi_mpd.~c
	
	cp $SCRIPT_DIR/rpi_mpd.~c /etc/mpd.conf
	rm $SCRIPT_DIR/rpi_mpd.~c $SCRIPT_DIR/rpi_mpd.~~c
	
	sudo /etc/init.d/mpd restart
fi

echo "run mpc update [y/n]?"
read MPD_UPDATE
if [ "$MPD_UPDATE" = "y" ] ; then    
    sudo /etc/init.d/mpd restart
    mpc update
fi
