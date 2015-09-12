#! /bin/bash

echo "ADD a NETWORK DIRECTORY AS MUSIC DIRECTORY:"
echo ""
echo "  addnetworkmusicdir NETDIRECTORY LOCAL_NAME [USERID]"
echo "  e.g. addnetworkmusicdir //JKDESKTOP/Musik jkdesktop_musik"
echo ""
echo "This script will :"
echo "  1. create an entry in /etc/fstab"
echo "  2. mount NETDIRECTORY to /mnt/LOCAL_NAME"
echo "  3. create a soft-link /home/USERID/music/LOCAL_NAME to this directory"
echo "  4. restart mpd and run mpc update"

CURRENTDIR=${PWD}
USERNAME=pi

FAST="0"
cd `dirname $0`
SCRIPT_DIR=`pwd`
cd $CURRENTDIR

NETDIR=//JKDESKTOP/Musik
LOCALNAME=jkdesktop_musik
if [ ! -z $1 ] ; then 
  NETDIR=$1
fi
if [ ! -z $2 ] ; then 
  LOCALNAME=$2
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
echo "NETDIRECTORY   = $NETDIR"
echo "LOCALNAME      = $LOCALNAME"
echo ""
echo "data OK [y/n]?"
read DATAOK
if [ "$DATAOK" = "y" ] ; then

	# make music directory in home
	MUSICDIR=$HOMEDIR/music
	mkdir -p /mnt/$LOCALNAME
	cd $MUSICDIR
	ln -s /mnt/$LOCALNAME
	cd $CURRENTDIR
	echo "\n# mount ${NETDIR} to /mnt/${LOCALNAME}\n${NETDIR} /mnt/${LOCALNAME} cifs auto,rw,uid=mpd,credentials=/etc/samba/mpd.credentials 0 0\n" >> /etc/fstab
	mount -a


	echo "run mpc update [y/n]?"
	read MPD_UPDATE
	if [ "$MPD_UPDATE" = "y" ] ; then    
		sudo /etc/init.d/mpd restart
		mpc update
	fi
fi
