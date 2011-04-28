<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?><?php

/* $Id: cancel.inc,v 1.10 2005/08/01 16:12:55 greggmc Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// For eGrad2000.com
// <jflemer@alum.rpi.edu>

	session_register('survey_id');
	session_register('survey_realm');
	if(ini_get('register_globals')) {
		$_SESSION['survey_id']    = &$survey_id;
		$_SESSION['survey_realm'] = &$survey_realm;
	}

	if(empty($_SESSION['survey_id'])) {
		// no survey INSERTed yet, so just go back to management interface
		$_SESSION['survey_id']    = '';
		$_SESSION['survey_realm'] = '';
		include(esp_where('index'));
		return;
	}

	$sql = "SELECT status FROM ".$GLOBALS['ESPCONFIG']['survey_table']." WHERE	id=".$_SESSION['survey_id'];
	$result = execute_sql($sql);
	if(count($result) < 1) {
		db_close($result);
		$_SESSION['survey_id']    = '';
		$_SESSION['survey_realm'] = '';
		include(esp_where('index'));
		return;
	}
	$status = $result->fields[0];
	db_close($result);
	$status |= STATUS_DELETED;
	$sql = "UPDATE ".$GLOBALS['ESPCONFIG']['survey_table']." SET status=${status} WHERE id=".$_SESSION['survey_id'];
	execute_sql($sql);
	$_SESSION['survey_id']    = '';
	$_SESSION['survey_realm'] = '';
	include(esp_where('index'));
	return;
?>