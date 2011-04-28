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
class Project {
//error_reporting(E_ALL);
//ini_set('display_errors', '1');

function init($project_id) { //a.k.a Get Project
	$this->id = $project_id;
	
	$this->id = preg_replace("/[^0-9]/i","",$this->id);
	$this->id = str_replace("'",'',$this->id);
	
	
	$getSQL = 'SELECT * FROM '.$GLOBALS['ESPCONFIG']['project_table']." WHERE id='$this->id'";
	$proj_result = execute_sql($getSQL);
	
	# if (!$proj_result) { echo mysql_error(); }
	# print_r($proj_result->fields);
	
	list(	$p['id'],
			$p['name'],
			$p['pre_id'],
			$p['post_id'],
			$p['intro'],
			$p['outro'],
			$p['goal'],
			$p['url'],
			$p['start'],
			$p['end'],
			$p['status'],
			$p['createstamp'],
			$p['editstamp'],
			$p['activestamp'],
			$p['completestamp'],
			$p['pre_source'],
			$p['post_source'] ) = $proj_result->fields;	
	
	$p = array_reverse($p);
	
	//load details
	$this->details = $p;
	//load surveys
	if ($this->details['pre_id']) $this->pre_survey = $this->get_survey($this->details['pre_id']);
	if ($this->details['post_id']) $this->post_survey = $this->get_survey($this->details['post_id']);
		
}
function create_project($data) {
	global $ESPCONFIG;

	require ESP_BASE.'admin/sanitize.php';
	$pname = sanitize($data['pname']);
	$ppre = sanitize($data['ppre']);
	$ppost = sanitize($data['ppost']);
	$pintro = sanitize($data['pintro']);
	$pthanks = sanitize($data['pthanks']);
	$pgoal = sanitize($data['pgoal']);
	$purl = sanitize($data['purl']);
	$pstart = sanitize($data['pstart']);
	$pend = sanitize($data['pend']);
	$pstatus = 1;
	
	if (!$pname) { $err[] = "You must enter a project name to continue.\n"; }
    if (!preg_match('|^http(s)?://[a-z0-9-]+(.[a-z0-9-]+)*(:[0-9]+)?(/.*)?$|i', $purl)){
		$err[] = "Your test URL appears to be formatted incorrectly. Please ensure that there is a proper prefix. (http://, ftp://, https://)</h2>";
	}
	if ($err) return $err;
	
	$sql = execute_sql("SELECT * FROM `".$ESPCONFIG[project_table]."` WHERE `name` = '".$pname."'");
	
	if (ErrorMsg()) $err[] = ErrorMsg();
	if ($err) return $err;
	
	if ($sql->RecordCount() > 0) {
		// Project already exists
		$err[] = "Project name '$pname' already exists.";
	}
	if ($err) return $err;
	
	
	$sqlins = 'insert into '.$ESPCONFIG[project_table].
	 ' (name,presurvey,postsurvey,action_intro_msg,action_outro_msg,goal,action_url,start,`end`,status,createstamp,editstamp) values ( '.
	"'$pname', ".
	"'$ppre', ".
	"'$ppost', ".
	"'$pintro', ".
	"'$pthanks', ".
	"'$pgoal', ".
	"'$purl', ".
	"'$pstart', ".
	"'$pend', ".
	"'$pstatus', ".
	"'".time()."', ".
	"'".time()."') ";
	
	$result = execute_sql($sqlins);
	if (ErrorMsg()) $err[] = ErrorMsg();
	if ($err) return $err;
	$_SESSION[pid] = mysql_insert_id();
	$projectid = $_SESSION[pid];
	
	// Insert into userprojectrel table
	$sqlins = "insert into userprojectrel values ('','".$_SESSION['acl']['userid']."','".$projectid."','Y')";
	
	$result = execute_sql($sqlins);
	if (ErrorMsg()) $err[] = ErrorMsg();
	if ($err) return $err;
	
	// Insert the root user record
	$sqlins = "insert into userprojectrel values ('','6','".$projectid."','Y')";
	if (ErrorMsg()) $err[] = ErrorMsg();
	if ($err) return $err;
	
	return $pname;
}
function delete() {
	require ESP_BASE.'admin/sanitize.php';
	global $ESPCONFIG;
	
	$dsql = "DELETE FROM $ESPCONFIG[project_table] WHERE id=".$this->id;
	$result = execute_sql($dsql);
	if (ErrorMsg()) $err[] = ErrorMsg();
	if ($err) return $err;
	return true;
}
function update($data,$options=null) {
	require ESP_BASE.'admin/sanitize.php';
	global $ESPCONFIG;
	$pid = $this->id;
	if ($data['pname']) { $u[name] = sanitize($data['pname']); }
	if ($data['ppre']) { $u[presurvey] = sanitize($data['ppre']); }
	if ($data['ppost']) { $u[postsurvey] = sanitize($data['ppost']); }
	if ($data['pintro']) { $u[action_intro_msg] = sanitize($data['pintro']); }
	if ($data['pthanks']) {$u[action_outro_msg] = sanitize($data['pthanks']); }
	if ($data['pgoal']) {$u[goal] = sanitize($data['pgoal']); }
	if ($data['purl']) { $u[action_url] = sanitize($data['purl']); }
	if ($data['pstart']) { $u[start] = sanitize($data['pstart']); }
	if ($data['pend']) { $u[end] = sanitize($data['pend']); }
	if ($data['status']) { $u[status] = sanitize($data['status']); }
	if ($data['pre_source']) { $u[pre_source] = sanitize($data['pre_source']); }
	if ($data['post_source']) { $u[post_source] = sanitize($data['post_source']); }
	
	
	foreach ($u as $key => $value) {
		if ($value == 'delete') {
			$u[$key] = '';
		}
	}
	$u[editstamp] = time();
	
	if ($u[status] == '2') {
		$u[activestamp] = time();
	}
	if ($u[status] == '3') {
		$u[completestamp] = time();
	}
	//Generate the Update sql
	$setsql = "SET ";
	foreach ($u as $key=>$d) {
		$setsql .= "$key = '$d', ";
	}
	$setsql = substr($setsql,0,-2);
	
	$usql = "UPDATE ".$ESPCONFIG[project_table]." ".$setsql." WHERE id='".$pid."'";
	//echo $usql;
	$result = execute_sql($usql);
	if (ErrorMsg()) $err[] = ErrorMsg();
	if ($err) return $err;
	return true;
}
function get_survey($id) {
	
	$getSQL = 'SELECT * FROM '.$GLOBALS['ESPCONFIG']['survey_table']." WHERE id='".$id."'";
	$survey_result = execute_sql($getSQL);
	$s = array();
	list(	$s['id'],
			$s['name'],
			$s['owner'],
			$s['realm'],
			$s['publicx'],
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
}//Class END
?>