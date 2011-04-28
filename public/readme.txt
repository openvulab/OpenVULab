RASCAL HOWTO

Overview

RASCAL or Remote Activity Screen Capture And Logger is a remote screen recording tool designed to capture the mouse, keyboard, screen, and audio of a user. It is used in conjunction with the VULab Web component to provide a full experience record for users doing usability tests with VULab.

RASCAL is also be a module that can be embedded into a webpage and screen recording can be captured.

Download

The latest build of RASCAL can be downloaded from http://rascal.xymbo.com/rascal.jar ;  you can also get the source from SVN https://source.fluidproject.org/svn/vulab/trunk/RASCAL/

Building

If you are building the source yourself, please ensure that you have the 1.5 or later version of the Java SDK.  Simply compile all the classes and JAR them.  Step-by-step instructions with screenshots for Eclipse will follow.

Installation

Simply copy the resulting JAR file and
http://rascal.xymbo.com/rascal.js  - the Javascript file, to your website's document root.  

Usage

Add the following code to your website to use RASCAL:
<APPLET name="rascal" ARCHIVE="rascal.jar" CODE=org.fluidproject.vulab.rascal.ui.ScreencastApplet.class WIDTH=0 HEIGHT=0 mayscript>
	<param name="java_arguments" value="-Xmx512m"/>
	<param name = "mode" value = "nogui"/>
</APPLET>

If you want to use the SWING UI in applet, simply remove the mode parameter.  Otherwise, please ensure that the javascript file is included in the page as well:
<script src="rascal.js"></script>

Using javascript calls, you can start, stop, query the recording, and get the id of the generated videos.  The javascript functions are fairly self explanatory:
	getSessionIdFromApplet() returns the id of the video created.  Should be 
		called after the video finishes recording.
	startRecordingApplet() starts the recording process.  This method should 	only be called if isRecordingApplet() returns false and getSessionIdFromApplet() returns -1
	stopRecordingApplet() stops the recording process.  This may take some time
		to complete as the streaming is a gating factor.  This method should not be considered completed until isRecordingApplet() returns false
	isRecordingApplet()  returns true iff the applet is not recording

You can view the source at http://rascal.xymbo.com to see how to use RASCAL with
javascript.

The generated files will end up at http://files.rascal.xymbo.com/<ID>.avi where <ID> is the id of the video.

Caveats

There are some jitter issues and other bugs documented in http://issues.fluidproject.org
