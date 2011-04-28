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
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
//File to Save Changes and Manage the PHP of Step 1
if ($_SESSION['mode'] == 'edit') {

	
	if ($_POST['pre_choose'] == 'none') {
		$data = array('ppre'=>'delete','pre_source'=>'delete');
		unset($_SESSION['pre_settings']['version']);
		$go = 3;
		$from = 2; 
		//echo "none";
	}
	elseif ($_POST['pre_choose'] == 'copy') {
	//	include(esp_where("survey_process"));
		$survey_processed = true;
		$sid = $_SESSION['survey_id'];
		$data = array('ppre'=>$sid,'pre_source'=>$_POST['copysurvey']);			
		$go = 3;
		$from = 2;
		//echo "copy";
	}
	elseif ($_POST['pre_choose'] == 'new') {
		//include(esp_where("survey_process"));
		if ($_POST['tab'] == 'General') {
			$_SESSION['pre_settings']['version'] = 'new';
//			$sql = "SELECT * FROM ".$GLOBALS['ESPCONFIG']['survey_table']." WHERE `name`='".$_POST['name']."'";
	//		$result = execute_sql($sql,"",ADODB_FETCH_ASSOC);
		//	$survey = fetch_row($result);
			
		}
			$survey_processed = true;
			$sid = $_SESSION['survey_id'];
			$data = array('ppre'=>$sid,'pre_source'=>'new');
		//echo "else";
	}
	//print_r($data);
	$editresult = $project->update($data);
	if (is_array($editresult)) {
		//set errors
		$err = $editresult;
	} else { //Set Success
		unset($project);
		$project = new Project;
		$project->init($_SESSION['pid']);
	}
}
	
if (is_array($err)) {
		$step = $from;
}
?>