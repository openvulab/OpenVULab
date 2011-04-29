openVULab 0.5
==================
Main Project Site:  https://github.com/openvulab/OpenVULab/
User Manual:        http://wiki.fluidproject.org/display/fluid/Open+Virtual+Usability+Lab
Public Project Demo:http://130.63.175.158/admin/manage.php
Blog:		    http://vulab.wordpress.com/

Twitter address: http://twitter.com/OpenVULab

What is openVULab
=================
OpenVULab is tool designed for remote usability research. A unique feature of VULab is that it can record video
and audio of remote users' interactions without the need to install an application on the users' computer.

When users log into OpenVULab they are presented with a series of pre-session questions set up by the researcher.
After answering these questions, users are directed to the web site or application being studied and recording
begins. Users then navigate the site according to protocols estabished by the researcher and they may be asked
to talk aloud about why they are making particular choices. At the end of the session the recording is stopped
and they are prompted to answer post-experience questions set up by the researcher. Users' pre- and post-session
questions and videos are stored so that they can be queried by the researcher and analyzed.

RASCAL, is the java component of openVULab that facilitates the audio/video capture during the study process.
It is nicely packaged into rascal.jar within the deployment bundle and is controlled through javascript.
(RASCAL's source can be found under the "Source Code" Section)

The source code will be available thtrough GIT as well. 


What's New in 0.5
=================

This release includes

    * Full Project Management
    * Powerful Survey Creation
    * Full Audio/Screen Capture
    * User Invitations and Signup
    * In-Frame URL Testing!


How to Install / Requirements
=============================
The installation guide can be found in INSTALL.txt


What's in this Release
======================

This release is available as a packaged file.
    vulab-0.5.rar- deployment bundle
    
Both bundles have the following organization:
		admin/        Administration interface and support files
		docs/         Survey Creation Documentation files
		images/       Image files
		locale/       Language files
		public/       Public interface to taking surveys
		scripts/      Database and other scripts
		files/	      Videos created by rascal are stored here
		infusion/     FluidProject Infusion library is here
		js/	      Javascript files used in vulab
		index.php	  Core php file that runs your openVULab
		rascal.jar	  The core RASCAL file that provides the screen/audio capture for surveys
        LICENSE.txt
        README.txt	
        INSTALL.txt	  Installation guide for openVULab
        
        phpESP-LICENSE.txt	Legacy phpESP license file - VULab 0.5 is build on phpESP

Source Code
-----------
The full source code for openVULab, including JavaScript, java, and php can be found in our source code repository:

	https://github.com/openvulab/OpenVULab/

Note that php is a non-compiled language so the package you downloaded IS the source, but the source code for RASCAL
that was compiled to provide your rascal.jar is located at:
	
	https://source.fluidproject.org/svn/vulab/trunk/RASCAL/


License
-------
openVULab code is licensed under a dual ECL 2.0 / BSD license. The specific licenses can be found
in the license file:
    LICENSE.txt

openVULab also depends upon some third party open source modules. These are contained in their own folders 
with their respective licenses inside the openVULab source code.


Third Party Software in openVULab
------------------------------
This is a list of publicly available software that is included in the Fluid bundle, along with their licensing terms.

	* jQuery javascript library: http://jquery.com/ (MIT and GPL licensed http://docs.jquery.com/Licensing)
	* jQuery UI javascript widget library: http://ui.jquery.com/ (MIT and GPL licensed http://docs.jquery.com/Licensing)
	* MPlayer and Mencoder library: http://www.mplayerhq.hu (GPL licensed http://www.mplayerhq.hu/design7/info.html#license)
	* FluidProject Infusion javascript Library http://fluidproject.org/products/infusion/

    
Readme
------
This file.
    README.txt


Documentation
=============

    http://wiki.fluidproject.org/display/fluid/Open+Virtual+Usability+Lab

openVULab is part of The Fluid Project and thus uses a wiki for documentation and project collaboration: http://wiki.fluidproject.org.

The User Manual for openVULab releases consists of a number of information pages stored in the Fluid Wiki with its home at:
http://wiki.fluidproject.org/display/fluid/Open+Virtual+Usability+Lab


Supported Browsers
==================
Firefox 2.x, 3.x: full support
Internet Explorer 6.x, 7.x: full support
Safari 3.1, Opera 9.5: full support (except keyboard interaction, which is not supported by these browsers)


Known Issues
============

openVULab uses a JIRA website to track bugs: http://issues.fluidproject.org/browse/VULAB.
Some of the known issues in this release are described here:

Feature: 
  A descrition of the known issue with the feature listed above, see http://link-to-issue-here.org/VULAB-666
    VULAB-666 Description of the issue from JIRA.

