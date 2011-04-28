#!/bin/sh


#Settings
MENCODER_LOCATION=`which mencoder`
UPLOAD_DIR='../files/'


#End Settings





cd $UPLOAD_DIR




Dirlist=$(find . -type d)
for direc in $Dirlist ; do
	echo "Testing $direc"
	if [ -f $direc/DONE.all ] 
	then
		echo "DONE.all exists"
		cd $direc
		fix_ts.sh $direc >/dev/null 2>&1
		sessionid=$direc
		silentmovie="$sessionid".silent.avi
		soundmovie="$sessionid".avi
		
		
		$MENCODER_LOCATION "mf://*.jpg" -mf fps=3 -o $silentmovie -ovc lavc -lavcopts vcodec=msmpeg4v2:vbitrate=800 
		$MENCODER_LOCATION $silentmovie -o $soundmovie -ovc copy -oac pcm  -audiofile output.wav >/dev/null 
		if [ -f $soundmovie ]
		then
		else
		  mv $silentmovie $soundmovie
		if
		
		mv $soundmovie ..
		cd ..
		rm -fr $sessionid

	else
		echo "DONE.all missing"
	fi
done
