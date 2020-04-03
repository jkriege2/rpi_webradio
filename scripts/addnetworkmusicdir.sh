#! /bin/bash

echo "ADD a NETWORK DIRECTORY AS MUSIC DIRECTORY:"
echo ""
echo "  addnetworkmusicdir NET_DIRECTORY LOCAL_NAME [YOUR_USERID]"
echo "  e.g. addnetworkmusicdir //JKDESKTOP/Musik jkdesktop_musik"
echo ""
echo "This script will :"
echo "  1. create an entry in /etc/fstab"
echo "  2. mount NET_DIRECTORY to /mnt/LOCAL_NAME"
echo "  3. create a soft-link /home/USERID/music/LOCAL_NAME to this directory"
echo "  4. restart mpd and run mpc update"

CURRENTDIR=${PWD}
USERNAME=pi

USE_AUTOFS="n"
ADD_CHRON_MOUNT="n"
FAST="0"
cd `dirname $0`
SCRIPT_DIR=`pwd`
cd $CURRENTDIR

NET_DIR=//JKDESKTOP/Musik
NET_NAME=jkdesktop_musik
if [ ! -z $1 ] ; then 
  NET_DIR=$1
fi
if [ ! -z $2 ] ; then 
  NET_NAME=$2
fi
if [ ! -z $3 ] ; then 
  USERNAME=$3
fi

HOMEDIR=/home/$USERNAME

echo ""
echo "CURRENTDIR = $CURRENTDIR"
echo "USERNAME   = $USERNAME"
echo "HOMEDIR    = $HOMEDIR"
echo "SCRIPT_DIR = $SCRIPT_DIR"
echo ""
echo ""
echo "NET_DIRECTORY   = $NET_DIR"
echo "NET_NAME        = $NET_NAME"
echo ""
echo "data OK [y/n]?"
read DATAOK
if [ "$DATAOK" = "y" ] ; then

#	# make music directory in home
#	MUSICDIR=$HOMEDIR/music
#	mkdir -p /mnt/$NET_NAME
#	cd $MUSICDIR
#	ln -s /mnt/$NET_NAME
#	cd $CURRENTDIR
#	echo "\n# mount ${NET_DIR} to /mnt/${NET_NAME}\n${NET_DIR} /mnt/${NET_NAME} cifs auto,rw,uid=mpd,credentials=/etc/samba/mpd.credentials 0 0\n" >> /etc/fstab
#	mount -a

	

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

	MOUNT_BASEDIR=/mnt
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
		LINE="$MOUNT_BASEDIR /etc/auto.smb-shares --ghost"
		if grep -q "${LINE}" "/etc/auto.master"; then
			echo "SMB-SHARES ENTRY ALREADY IN /etc/auto.master"
		else
			echo "CREATEING SMB-SHARES ENTRY IN /etc/auto.master"
			echo "\n${LINE}\n" >> /etc/auto.master
		fi
	else
		echo "\n# mount ${NET_DIR} to ${MOUNT_BASEDIR}/${NET_NAME}\n${NET_DIR} ${MOUNT_BASEDIR}/${NET_NAME} cifs auto,rw,uid=mpd,credentials=/etc/samba/$NET_NAME.credentials 0 0\n" >> /etc/fstab
		mount -a
		
		if [ "$ADD_CHRON_MOUNT" = "y" ] ; then
			command="/bin/mount -a > /dev/null 2>&1"
			job="*/2 * * * * $command"
			cat <(fgrep -i -v "$command" <(crontab -l)) <(echo "$job") | crontab -
		fi
	fi
	
	cd $MUSICDIR
	ln -s $MOUNT_BASEDIR/$NET_NAME
	cd $CURRENTDIR
	

	
	echo "run mpc update [y/n]?"
	read MPD_UPDATE
	if [ "$MPD_UPDATE" = "y" ] ; then    
		sudo /etc/init.d/mpd restart
		mpc update
	fi
fi
