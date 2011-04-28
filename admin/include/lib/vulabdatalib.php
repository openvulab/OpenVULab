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
function get_surveys() {
	if($_SESSION['acl']['superuser'] == 'Y') {
		$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
		FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s WHERE s.status = 0 ORDER BY s.id DESC";
	} else {
		$realms = array_to_insql(
		array_intersect(
		$_SESSION['acl']['pall'],
		$_SESSION['acl']['pdesign']));
		$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
			FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s WHERE s.status = 0 AND (s.owner = ".
		_addslashes($_SESSION['acl']['username']) ." || s.realm $realms) ORDER BY id DESC";
	}
	$result = execute_sql($sql);

	$survey_opts = "";

	
	return $result;
}
///////////
// MOD - GET ALL SURVEYS
///////////
function get_surveys_all() {
	if($_SESSION['acl']['superuser'] == 'Y') {
		$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
		FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s ORDER BY s.id DESC";
	} else {
		$realms = array_to_insql(
		array_intersect(
		$_SESSION['acl']['pall'],
		$_SESSION['acl']['pdesign']));
		$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
			FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s WHERE s.status = 0 AND (s.owner = ".
		_addslashes($_SESSION['acl']['username']) ." || s.realm $realms) ORDER BY id DESC";
	}
	$result = execute_sql($sql);

	$survey_opts = "";

	
	return $result;
}
///////////
// - MOD END - GET ALL SURVEYS
///////////
///////////
// MOD - GET ALL ASSIGNED/COMPLETE (AKA ACTIVE) SURVEYS
///////////
function get_surveys_assigned() {
	if($_SESSION['acl']['superuser'] == 'Y') {
		$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
		FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s WHERE s.status != 0 ORDER BY s.id DESC";
	} else {
		$realms = array_to_insql(
		array_intersect(
		$_SESSION['acl']['pall'],
		$_SESSION['acl']['pdesign']));
		$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
			FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s WHERE s.status = 0 AND (s.owner = ".
		_addslashes($_SESSION['acl']['username']) ." || s.realm $realms) ORDER BY id DESC";
	}
	$result = execute_sql($sql);

	$survey_opts = "";

	
	return $result;
}
///////////
// - MOD END - GET ALL ASSIGNED/COMPLETE (AKA ACTIVE) SURVEYS
///////////
function get_projects() {
	if($_SESSION['acl']['superuser'] == 'Y') {
		$sql2 = "SELECT p.id, p.name, p.presurvey, p.postsurvey, 
		p.action_intro_msg, p.action_outro_msg, p.action_url 
		FROM ".$GLOBALS['ESPCONFIG']['project_table']." p";
	} else {
//		$realms = array_to_insql(
//		array_intersect(
//		$_SESSION['acl']['pall'],
//		$_SESSION['acl']['pdesign']));
//		$sql = "SELECT s.id, s.name, s.title, s.owner, s.realm
//			FROM ".$GLOBALS['ESPCONFIG']['survey_table']." s WHERE s.status = 0 AND (s.owner = ".
//		_addslashes($_SESSION['acl']['username']) ." || s.realm $realms) ORDER BY id DESC";
		$sql = "SELECT * FROM `userprojectrel` WHERE `userid` = '".$_SESSION['acl']['userid']."' AND `admin` = 'Y'";
		$result = execute_sql($sql);
		
		if ($result->RecordCount() > 1)
		{
			$sql2Suffix = "`id` = '".$result->fields[2]."'";
			$result->MoveNext();
			while (!$result->EOF) {
				$sql2Suffix .= " OR `id` = '".$result->fields[2]."'";;
				$result->MoveNext();
			}
		}
		else
			$sql2Suffix = "`id` = '".$result->fields[2]."'";
		$sql2 = "SELECT * FROM ".$GLOBALS['ESPCONFIG']['project_table']." WHERE ".$sql2Suffix;
	}
	$project_result = execute_sql($sql2);
	$survey_opts = "";
	
	return $project_result;
}

///////////
// MOD - Delete Project(s)
///////////
function rm_projects($projects = array(),$options=NULL) {
//	if($_SESSION['acl']['superuser'] == 'Y') {
	
		//Lets remove any empty fields from $projects array
		foreach ($projects as $key=>$val)
		{
			if (!$projects[$key]) { unset($projects[$key]); }
		}
		//Make sure a project was submitted
		if (!$projects[0]) { return false; }
		
		//Create all of the sql statements for each project and save in $rm_projects_sql[]
		foreach ($projects as $project) {
			$rm_projects_sql[] = "DELETE FROM ".$GLOBALS['ESPCONFIG']['survey_table']." WHERE id='$project[id]' AND status";
		}
		echo '<pre>';
		print_r($rm_projects_sql);
		echo '</pre>';
//	}

}
// - MOD END - Delete Project(s)

///////////
// MOD - Delete Surveys(s)
function rm_surveys($surveys = array(),$options=NULL) {

//	if($_SESSION['acl']['superuser'] == 'Y') {
	
		//Lets remove any empty fields from $surveys array
		foreach ($surveys as $key=>$val)
		{
			if (!$surveys[$key]) { unset($surveys[$key]); }
		}
		//Make sure a project was submitted
		if (!$surveys[0]) { return false; }
		
		//Create all of the sql statements for each project and save in $rm_projects_sql[]
		foreach ($projects as $project) {
			$rm_projects_sql[] = "DELETE FROM ".$GLOBALS['ESPCONFIG']['project_table']." WHERE id='$project[id]'";
		}
		echo '<pre>';
		print_r($rm_projects_sql);
		echo '</pre>';
//	}

}
// - MOD END - Delete Surveys(s)
///////////
function get_tests() {
	/*if($_SESSION['acl']['superuser'] == 'Y') {
		$sql2 = "SELECT p.id, p.name, p.presurvey, p.postsurvey, 
		p.action_intro_msg, p.action_outro_msg, p.action_url 
		FROM ".$GLOBALS['ESPCONFIG']['project_table']." p";
	} else {*/
		$sql = "SELECT * FROM `userprojectrel` WHERE `userid` = '".$_SESSION['acl']['userid']."' AND `admin` = 'N'";
		$result = execute_sql($sql);
		
		if ($result->RecordCount() > 1)
		{
			$sql2Suffix = "`id` = '".$result->fields[2]."'";
			$result->MoveNext();
			while (!$result->EOF) {
				$sql2Suffix .= " OR `id` = '".$result->fields[2]."'";;
				$result->MoveNext();
			}
		}
		else
			$sql2Suffix = "`id` = '".$result->fields[2]."'";
		$sql2 = "SELECT * FROM ".$GLOBALS['ESPCONFIG']['project_table']." WHERE ".$sql2Suffix;
	//}
	$project_result = execute_sql($sql2);
	$survey_opts = "";
	
	return $project_result;
}

?>