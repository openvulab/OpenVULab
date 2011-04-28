<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/

# define base path
if (!defined('ESP_BASE')) define('ESP_BASE', dirname(dirname(__FILE__)) .'/');
if (!defined('CORE_BASE')) define('CORE_BASE', dirname(dirname(__FILE__)) .'/');

# define error reporting
error_reporting(E_ALL ^ E_NOTICE);

# clear all old configs
unset($CONFIG);

# clean up HTTP_HOST for config switching
$host = explode(':',$_SERVER['HTTP_HOST']);
	switch($host[0]) {
		
		case 'vulab.localhost':
			include(CORE_BASE.'admin/config.localhost.php');
			break;
		default:
			#include (CORE_BASE.'admin/config.legacylive.php');
			include (CORE_BASE.'admin/config.live.php');
			break;
	}
?>