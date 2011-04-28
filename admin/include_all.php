<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
	
	if (!defined('CORE_BASE')) define('CORE_BASE', dirname(dirname(__FILE__)) .'/');

	# include session management
	include(CORE_BASE.'/admin/include/lib/vulab.sessions.php');
	
	# include database management
	include(CORE_BASE.'/admin/include/lib/vulab.databases.php');
	
	# include configuration
	include(CORE_BASE.'/admin/config.inc.php');
		
	///Include Our Libraries
	require_once ($CONFIG['path']['include']."/lib/vulabdatalib.php");
	require_once ($CONFIG['path']['include']."/lib/vulab.functions.php");
	require_once ($CONFIG['path']['include']."/lib/vulab.projects.class.php");
	require_once ($CONFIG['path']['include']."/lib/vulab.projects.function.php");
	require_once ($CONFIG['path']['include']."/lib/vulab.users.class.php");
	require_once ($CONFIG['path']['include']."/lib/vulab.users.function.php");
	require_once ($CONFIG['path']['include']."/lib/vulab.surveys.class.php");
	require_once ($CONFIG['path']['include']."/lib/vulab.debugger.php");
	require_once ($CONFIG['path']['include']."/lib/vulab.permissions.class.php");
	
?>