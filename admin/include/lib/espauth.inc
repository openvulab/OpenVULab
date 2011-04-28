<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?>
<?php

/* $Id: espauth.inc,v 1.14 2007/11/26 11:36:17 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

//  phpESP Authentication Library Chooser
//  By: James Flemer <jflemer@alum.rpi.edu>

	$auth_type = $GLOBALS['ESPCONFIG']['auth_type'];
	if (empty($auth_type))
		$auth_type = 'default';
	if (preg_match("/manage.php/",$ESPCONFIG['ME']) &&
	    ($auth_type == 'ldap_both' || $auth_type == 'ldap_des')) {
		$auth_type = 'ldap';
	} else if (!preg_match("/manage.php/",$ESPCONFIG['ME']) &&
		($auth_type == 'ldap_both' || $auth_type == 'ldap_resp')) {
		$auth_type = 'ldap';
	} else {
		$auth_type = 'default';
	}

	if (!file_exists($GLOBALS['ESPCONFIG']['include_path']."/lib/espauth-$auth_type".$ESPCONFIG['extension'])) {
		echo("<b>FATAL: Unable to set up authentication for type $auth_type. Aborting.</b>");
		exit;
	}

	require($ESPCONFIG['include_path']."/lib/espauth-$auth_type".$ESPCONFIG['extension']);

?>