#! /bin/sh

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

USE_AUTOFS="n"
ADD_CHRON_MOUNT="n"



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
	

	#install boost
	apt-get install libboost-all-dev
	
	#install cairo etc.
	apt-get install libpixman-1-dev libcairo2 libcairo2-dev

	# install alsa
	sudo apt-get install alsa-base alsa-utils

	# install mpd, libmpdcleint, mpc
	apt-get install mpd mpc libmpdclient2
	
	
	# install samba-client
	apt-get install smb-client 
	
	# install cron
	apt-get install cron
	
	# optionally install autofs
	if [ "$USE_AUTOFS" = "y" ] ; then
		apt-get install autofs
	fi


	cd $HOMEDIR
	# clone and install wiringPi
	git clone git://git.drogon.net/wiringPi
	cd wiringPi
	./build
	cd $CURRENTDIR

fi

echo "\n\nauto-start mpd [y/n]?"
echo "      default:y"
read AUTOSTART_MPD
if [ "$AUTOSTART_MPD" = "y" ] ; then
	if grep -q "[ ! -s ~/.config/mpd/pid ] && mpd" "$HOMEDIR/.profile"; then
		echo "AUTOSTART ENTRY ALREADY IN ${HOMEDIR}/.profile"
	else
		echo "CREATEING AUTOSTART ENTRY IN ${HOMEDIR}/.profile"
		echo "\n# MPD daemon start (if no other user instance exists)\n[ ! -s ~/.config/mpd/pid ] && mpd\n" >> $HOMEDIR/.profile
	fi
	
fi

if [ "$USE_AUTOFS" = "n" ] ; then
	echo "\n\nstart a chron job to automatically update the mounts every 2 minutes [y/n]?"
	echo "      default:y"
	read ADD_CHRON_MOUNT
fi

# activate sound drivers for ES9023 or hifiberry-dac, see e.g. http://www.linuxmediaserver.net/howto/openelec-es9023-using-i2s/
echo "\n\nwhich Audio-hardware do you want to use?"
echo "  - 1: HifiBerry-DAC / ES9023"
echo "  - ENTER [default]: no special hardware/default hardware/USB/... "  
read AUDIOHW
if [ "$AUDIOHW" = "1" ] ; then
	echo "\nsnd_soc_bcm2708\nsnd_soc_bcm2708_i2s\nbcm2708_dmaengine\nsnd_soc_pcm5102a\nsnd_soc_hifiberry_dac\n" >> /etc/modules
	echo "\ndtoverlay=hifiberry-dac\n" >> /boot/config.txt
fi


# make music directory in home
MUSICDIR=$HOMEDIR/music
mkdir -p $MUSICDIR
mkdir -p $MUSICDIR/mpd/playlists


MOUNT_BASEDIR=/mnt
echo "\n\nMount network music directory [y/n]?"
read NET_MOUNT
if [ "$NET_MOUNT" = "y" ] ; then
    echo "enter path:"  
	read NET_DIR
	echo "enter name for this collection:"  
	read NET_NAME

	echo "Do you need username/password for access [y/n]?"
	read NET_MOUNT_CREDENTIALS_REQUIRED
	NET_MOUNT_CREDENTIALS_USER=""
	NET_MOUNT_CREDENTIALS_PASSWORD=""
	if [ "$NET_MOUNT_CREDENTIALS_REQUIRED" = "y" ] ; then
		echo "  -> enter username:"
		read NET_MOUNT_CREDENTIALS_USER
		echo "  -> enter password:"
		read NET_MOUNT_CREDENTIALS_PASSWORD
	fi
	
	echo "# USERNAME and PASSWORD for NAS-access (if required)\nusername=${NET_MOUNT_CREDENTIALS_USER}\npassword=${NET_MOUNT_CREDENTIALS_PASSWORD}\n" > /etc/samba/$NET_NAME.credentials
	chown -R $USERNAME /etc/samba/$NET_NAME.credentials
	sudo chmod 666 /etc/samba/$NET_NAME.credentials
	chown -R $USERNAME $MUSICDIR
	chmod -R 777 $MUSICDIR
	echo "\nNOTE: You can edit the user-redentials for your new network directory "
	echo "in the file /etc/samba/$NET_NAME.credentials !"

	if [ "$USE_AUTOFS" = "y" ] ; then
		MOUNT_BASEDIR=/mnt/smb/
		mkdir -p $MOUNT_BASEDIR
	else
		MOUNT_BASEDIR=/mnt
	fi

	mkdir -p $MOUNT_BASEDIR/$NET_NAME
		
	if [ "$USE_AUTOFS" = "y" ] ; then
		echo "\n$NET_NAME -fstype=cifs,uid=1000,credentials=/e
		tc/samba/$NET_NAME.credentials :$NET_DIR\n" >> /etc/auto.smb-shares
		LINE="${MOUNT_BASEDIR} /etc/auto.smb-shares --ghost"
		if grep -q "${LINE}" "/etc/auto.master"; then
			echo "SMB-SHARES ENTRY ALREADY IN /etc/auto.master"
		else
			echo "CREATEING SMB-SHARES ENTRY IN /etc/auto.master"
			echo "\n${LINE}\n" >> /etc/auto.master
		fi
	else
		echo "\n# mount ${NET_DIR} to ${MOUNT_BASEDIR}/${NET_NAME}\n${NET_DIR} ${MOUNT_BASEDIR}/${NET_NAME} cifs auto,rw,uid=mpd,credentials=/etc/samba/$NET_NAME.credentials 0 0\n" >> /etc/fstab
		mount -a
	fi
	
	cd $MUSICDIR
	ln -s $MOUNT_BASEDIR/$NET_NAME
	cd $CURRENTDIR
	
fi

if [ "$USE_AUTOFS" = "n" ] ; then
	echo "\n# mount ${NET_DIR} to ${MOUNT_BASEDIR}/${NET_NAME}\n${NET_DIR} ${MOUNT_BASEDIR}/${NET_NAME} cifs auto,rw,uid=mpd,credentials=/etc/samba/$NET_NAME.credentials 0 0\n" >> /etc/fstab
	mount -a
	
	if [ "$ADD_CHRON_MOUNT" = "y" ] ; then
		command="/bin/mount -a > /dev/null 2>&1"
		job="*/2 * * * * $command"
		echo "$job" > /etc/cron.d/automount.cron
		echo "added chron-job"
		service cron restart
	fi
fi

echo "\n\nOverwrite /etc/mpd.config with customized/taylored version [y/n]?"
echo "      default:y"
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

echo "\n\nrun mpc update [y/n]?"
echo "      default:y"
read MPD_UPDATE
if [ "$MPD_UPDATE" = "y" ] ; then    
    sudo /etc/init.d/mpd restart
    mpc update
fi
