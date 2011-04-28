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
class Survey {

function __construct($survey_id,$data=NULL) { //a.k.a Get Project
	if (!$survey_id OR strtolower($survey_id) == 'new') {
		//echo "<pre>";print_r($data);echo "</pre>";
		if ($data) {
			$newsurvey = $this->create_survey($data);
			if (!$newsurvey) { echo "Error creating surey!:".$errstr; }
		}
	}
	$this->id = $survey_id;
	
		
}
function create_survey($data) {
	$f_arr = array();
	$v_arr = array();
// need to fill out at least some info on 1st tab before proceeding
		if(empty($data['name']) || empty($data['title']) || empty($data['realm'])) {
			$tab = "general";
			$errstr = _('Sorry, please fill out the name, group, and title before proceeding.');
			return(0);
		}

		// create a new survey in the database
		$fields = array('name','realm','title','subtitle','email','theme','thanks_page','thank_head','thank_body','info','auto_num');
		foreach($fields as $f) {
			if(isset($data[$f])) {
				array_push($f_arr,$f);
				array_push($v_arr, _addslashes($data[$f]));
			}
		}
		array_push($f_arr, 'owner');
		array_push($v_arr, _addslashes($_SESSION['acl']['username']));
		array_push($f_arr, 'changed');
		array_push($v_arr, sys_time_stamp());
		$sql = "INSERT INTO ".$GLOBALS['ESPCONFIG']['survey_table']." (" . join(',',$f_arr) . ") VALUES (" . join(',',$v_arr) . ")";
		$result = execute_sql($sql);
		if(!$result) {
			$errstr = _('Sorry, name already in use. Pick a new name.') .' [ ' .ErrorNo().': '.ErrorMsg().' ]';
			return(0);
		}

		$sql = "SELECT id FROM ".$GLOBALS['ESPCONFIG']['survey_table']." WHERE name=".  _addslashes($data['name']);
		$result = execute_sql($sql);
		$survey_id = $result->fields[0];
		return(1);
}
function get_survey($id) {
	
	$getSQL = 'SELECT * FROM '.$GLOBALS['ESPCONFIG']['survey_table']." WHERE id='".$id."'";
	$survey_result = execute_sql($getSQL);
	$s = array();
	list(	$s['id'],
			$s['name'],
			$s['owner'],
			$s['realm'],
			$s['public'],
			$s['status'],
			$s['title'],
			$s['email'],
			$s['subtitle'],
			$s['info'],
			$s['theme'],
			$s['thanks_url'],
			$s['thanks_head'],
			$s['thanks_body']) = $survey_result->fields;
			
	return array_reverse($s);
}
function update($data,$options=null) {

	global $ESPCONFIG;

	$sid = $this->id;

	if ($data['status']) { $s[status] = $data['status']; }
	if ($data['owner']) { $s[owner] = $data['owner']; }
	if ($data['name']) { $s[name] = $data['name']; }
	if ($data['realm']) { $s[realm] = $data['realm']; }
	if ($data['public']) { $s[owner] = $data['public']; }
	if ($data['title']) { $s[title] = $data['title']; }
	if ($data['email']) { $s[email] = $data['email']; }
	if ($data['subtitle']) { $s[subtitle] = $data['subtitle']; }
	if ($data['info']) { $s[info] = $data['info']; }	
	if ($data['theme']) { $s[theme] = $data['theme']; }
	if ($data['thanks_page']) { $s[thanks_page] = $data['thanks_page']; }
	if ($data['thank_head']) { $s[thank_head] = $data['thank_head']; }
	if ($data['thank_body']) { $s[thank_body] = $data['thank_body']; }
	if ($data['changed']) { $s[changed] = $data['changed']; }
	if ($data['auto_num']) { $s[auto_num] = $data['audo_num']; }
	if ($data['userid']) { $s[userid] = $data['userid']; }
	if ($data['pid']) { $s[pid] = $data['pid']; }
	if ($data['history']) { $s[history] = $data['history']; }
        if ($data['PublicSurvey']) { $s[owner] = $data['PublicSurvey']; }
	
	foreach ($s as $key=>$value) {
		if ($value == 'delete') {
			$s[$key] = '';
		}
	}
/*	$s[editstamp] = time();
	
	if ($u[status] == '2') {
		$u[activestamp] = time();
	}
*/
	//Generate the Update sql
	$setsql = "SET ";
	foreach ($s as $key=>$d) {
		$setsql .= "$key = '$d', ";
	}
	$setsql = substr($setsql,0,-2);
	
	$usql = "UPDATE ".$ESPCONFIG[survey_table]." ".$setsql." WHERE id='".$sid."'";
	//echo $usql;
	$result = execute_sql($usql);
	if (ErrorMsg()) $err[] = ErrorMsg();
	if ($err) return $err;
	return true;
}

}//Class END
?>