<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
	
/// Options to Change
//error_reporting(E_ALL);
	//ini_set('display_errors', '1');
	# database configuration
	$db['main']['host'] = 'localhost';
	$db['main']['dbname'] = 'vulab_vulab';
	$db['main']['user'] = 'dbUser';
	$db['main']['pass'] = 'dbPass';
	$db['main']['link'] = dbConnect('main');

	# http or https?
	$CONFIG['url']['proto'] = 'http://';
	
	
	# If you have installed OpenVuLab in a subdirectory (ex. domain.com/folder/vulab) enter it below:
	# - DO NOT ADD A TRAILING SLASH
	# - If its installed in the root of the domain (ex. domain.com/index.php) leave this blank.
	$CONFIG['url']['subdir'] = '';

	# base URL
	$CONFIG['url']['base'] = $CONFIG['url']['proto'] . $server['HTTP_HOST'] . $CONFIG['url']['subdir'];
	
	# url of the images directory (for <img src='...'> tags)
	$CONFIG['url']['images'] = $CONFIG['url']['base'] . $CONFIG['url']['subdir'] . '/images/';

	# url for logo
	$CONFIG['url']['logo'] = $CONFIG['url']['images'] . 'OpenVULab.png';
	
	# url of the css directory (for themes)
	$CONFIG['url']['css'] = $CONFIG['url']['base'] . '/public/css/';


	$CONFIG['path']['include'] = CORE_BASE . '/admin/include/';
	$CONFIG['path']['css'] = CORE_BASE . '/public/css/';
	$CONFIG['path']['locale'] = CORE_BASE . '/locale';

	# url for management javascript
	$CONFIG['url']['js'] = $CONFIG['url']['base'] . '/js/';
	
	$CONFIG['version'] = '0.3 alpha';
	
/// Site Options
	$SITE['name'] = 'OpenVULab';
	$SITE['slogan'] = 'Remote Usability Testing Suite';
	# HTML page title
	$SITE['title'] = $SITE['name'] .', v('. $CONFIG['version'].')';


//// Options for the Experienced

	include (CORE_BASE.'admin/phpESP.ini-local.php');
 ?>