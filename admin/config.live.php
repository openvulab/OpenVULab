<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/

error_reporting(E_ALL);
	ini_set('display_errors', '1');
	
/// Options to Change

	# database configuration
	$db['main']['host'] = 'localhost';
	$db['main']['dbname'] = 'eblake_vudev';
	$db['main']['user'] = 'eblake_vudbuse';
	$db['main']['pass'] = 'vudbpass';
	$db['main']['link'] = dbConnect('main');


	# http or https?
	$CONFIG['url']['proto'] = 'http://';
	
	
	# If you have installed OpenVuLab in a subdirectory (ex. domain.com/folder/vulab) enter it below:
	# - DO NOT ADD A TRAILING SLASH
	# - If its installed in the root of the domain (ex. domain.com/index.php) leave this blank.
	$CONFIG['url']['subdir'] = '';

	# base URL
	$CONFIG['url']['base'] = $CONFIG['url']['proto'] . $_SERVER['HTTP_HOST'] . $CONFIG['url']['subdir'];
	
	
	# url of the images directory (for <img src='...'> tags)
	$CONFIG['url']['images'] = $CONFIG['url']['base'] . $CONFIG['url']['subdir'] . '/images/';

	# url for logo
	$CONFIG['url']['logo'] = $CONFIG['url']['images'] . 'OpenVULab.png';
	
	# url of the css directory (for themes)

	$CONFIG['url']['css'] = $CONFIG['url']['base'] . '/public/css/';

	$CONFIG['path']['include'] = CORE_BASE . 'admin/include/';
	$CONFIG['path']['css'] = CORE_BASE . 'public/css/';
	$CONFIG['path']['locale'] = CORE_BASE . 'locale';
	
	# some files
        if(@$_GET['where']=="survey_tool"){
            $CONFIG['url']['admin-css'] = $CONFIG['url']['base'].'/infusion/components/inlineEdit/css/InlineEdit.css';
        }else{
            $CONFIG['url']['admin-css'] = $CONFIG['url']['base'].'/admin/style.css';
        }
	

	# url for management javascript
	$CONFIG['url']['js'] = $CONFIG['url']['base'] . '/js/';
	
	$CONFIG['version'] = '0.5b';



/// Site Options
	
	$SITE['name'] = 'OpenVULab';
	$SITE['slogan'] = 'Remote Usability Testing Suite';
	# HTML page title
	$SITE['title'] = $SITE['name'] .', v('. $CONFIG['version'].')';
	
// Email Options
	
	// please use valid emails
	$CONFIG['email']['admin_address'] = "openVuLab"; # will be used to receieve various notifications
	$CONFIG['email']['from_name'] = "openVuLab"; # will be used when sending emails to users
	$CONFIG['email']['from_address'] = "vulab@". $_SERVER['SERVER_NAME']; # will be used when sending emails to users

//// Options for the Experienced

	include (CORE_BASE.'admin/config.legacylive.php');
 ?>