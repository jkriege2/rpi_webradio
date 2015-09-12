#! /bin/bash

echo "THIS TOOL HELPS TO EDIT WEBRADIO STATIONS:"
echo "  editwebradiostations [USERID]"

CURRENTDIR=${PWD}
USERNAME=pi

cd `dirname $0`
SCRIPT_DIR=`pwd`
cd $CURRENTDIR

if [ ! -z $1 ] ; then 
  USERNAME=$1
fi

HOMEDIR=/home/$USERNAME
MUSICDIR=$HOMEDIR/music
PLAYLISTDIR=$MUSICDIR/mpd/playlists
WEBRADIO_PLAYLIST=$PLAYLISTDIR/webradio.m3u

echo ""
echo "CURRENTDIR = $CURRENTDIR"
echo "USERNAME   = $USERNAME"
echo "HOMEDIR    = $HOMEDIR"
echo "SCRIPT_DIR = $SCRIPT_DIR"
echo ""
echo "MUSICDIR            = $MUSICDIR"
echo "PLAYLISTDIR         = $PLAYLISTDIR"
echo "WEBRADIO_PLAYLIST   = $WEBRADIO_PLAYLIST"
echo ""
echo "data OK [y/n]?"
read DATAOK
if [ "$DATAOK" = "y" ] ; then
	if [ ! -e "${WEBRADIO_PLAYLIST}" ] ; then
		cp $SCRIPT_DIR/default_webradio.m3u $WEBRADIO_PLAYLIST
	fi
	
	nano $WEBRADIO_PLAYLIST
	
	
	echo "run mpc update [y/n]?"
	read MPD_UPDATE
	if [ "$MPD_UPDATE" = "y" ] ; then    
		sudo /etc/init.d/mpd restart
		mpc update
	fi
	
fi
