<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
/*
File: 		vulab.users.class.php \\v 1.0
Info:		- the User object: $user = new User($userid);
Author: 	Blake Edwards
Email:		electBlake@gmail.com

License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
*/
class User {

function __construct($userid=NULL) { //a.k.a Get Project
	$this->id = $userid;
	$getSQL = 'SELECT * FROM '.$GLOBALS['ESPCONFIG']['user_table']." WHERE userid='$this->id'";

	$user_result = execute_sql($getSQL);
	//print_r($proj_result->fields);
	
	list(	$u['userid'],
				$u['username'],
				$u['password'],
				$u['fname'],
				$u['lname'],
				$u['email'],
				$u['researcher'],
				$u['disabled']) = $user_result->fields;	

	
	$u = array_reverse($u);
	
	//load details
	$this->details = $u;

}

function email($subject,$message,$options = NULL) {
	
	global $CONFIG;
	global $SITE;
	
	$from 	 = ($options['from'] ? $options['from'] : 'mail@vulab.yorku.ca');
	$reply 	 = ($options['reply'] ? $options['reply'] : 'no-reply@vulab.yorku.ca');
	$pid	 = $options['pid'];

	if (strtolower($options['type']) == 'welcome') {
		global $_POST;
		$password = $_POST['password'];
		$subject = 'Welcome to '.$SITE['name'];
		$message = 'Welcome to '.$SITE['name']."\n\n";
		$message .= "Username: ".$this->details[username]."\n";
		$message .= "Passowrd: ".$password."\n";
		$message .= "\n \n You have been signed up on ".$CONFIG[url][base]."\n\n";
	}
	
	$emailid = explode('@',$this->details['email']);
	
	$toName  = ($this->details['fname'] ? $this->details['fname'] : $emailid[0]);
	$to      = $toName." <".$this->details['email'].">";
	$headers = 'From: '.$from. "\r\n" .
	    'Reply-To: '.$reply ."\r\n" .
	    'X-Mailer: PHP/' . phpversion();
	    
	    
	//Replace Variables in Message
	foreach ($this->details as $key=>$value) {
		$message = str_replace("<user-$key>",$value,$message);
	}
	
	if ($pid) {
		$project = new Project;
		$project->init($pid);
		if ($project->details) {
			foreach ($project->details as $key=>$value) {
				$message = str_replace("<project-$key>",$value,$message);
			}
		}
	}
	
	return mail($to, $subject, $message, $headers);
	

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
	if ($data['purl']) { $u[action_url] = sanitize($data['purl']); }
	if ($data['pstart']) { $u[start] = sanitize($data['pstart']); }
	if ($data['pend']) { $u[end] = sanitize($data['pend']); }
	if ($data['status']) { $u[status] = sanitize($data['status']); }
	if ($data['pre_source']) { $u[pre_source] = sanitize($data['pre_source']); }
	if ($data['post_source']) { $u[post_source] = sanitize($data['post_source']); }
	
	
	foreach ($u as $key=>$value) {
		if ($value == 'delete') {
			$u[$key] = '';
		}
	}
	$u[editstamp] = time();
	
	if ($u[status] == '2') {
		$u[activestamp] = time();
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

}//Class END
?>