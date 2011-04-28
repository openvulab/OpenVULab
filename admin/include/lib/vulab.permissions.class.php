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
File: 		vulab.permissions.class.php \\v 1.0
Info:		- manage permissions Class
Author: 	Blake Edwards
Email:		electBlake@gmail.com

License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
*/
class Perm {

function __construct($type,$id) { 
	$this->type = $type;
	$this->id = $id;
	$this->table = 'userprojectrel';
	if ($this->type == 'project') {
		$p = new Project;
		$p->init($this->id);
		$this->project = $p;
	}
	if ($this->type == 'user') {
		//$this->user = new User($this->id);
	}
	if ($this->type == 'survey') {
		//$this->survey = new Survey($this->id);
	}
}
function checkUser($pid) {
	$uid = $this->id;
	$dsql = "SELECT * FROM $this->table WHERE userid='$uid' AND projectid='$pid'";
	$dresult = execute_sql($dsql);
	if ($dresult->RecordCount() > 0) {
		return true;
	} else {
		return false;
	}
}
function assignUser($pid,$perm='N') {
	$uid = $this->id;
	$dsql = "SELECT * FROM $this->table WHERE userid='$uid' AND projectid='$pid' AND admin='$perm'";
	$dresult = execute_sql($dsql);
	if (ErrorMsg()) $err[] = ErrorMsg();
	if ($err) return $err;
	
	if ($dresult->RecordCount() > 0) {
		return array("Error: The UserID:$uid has already been added to ProjectID:$pid with Admin: $perm");
	} else {
		$sql = "INSERT INTO $this->table (id, userid, projectid, admin) VALUES ('','$uid','$pid','$perm')";
		$result = execute_sql($sql);
		if (ErrorMsg()) $err[] = ErrorMsg();
		if ($err) return $err;
		if (!$result) {
			return array('Error Adding User to Project ID:'.$pid);
		} else {
			return "Successfully Added UserID:$this->id to ProjectID:$pid with Admin: $perm";
		}
	}
}
/*
function removeUser($uid,$pid) {
	$sql = 'DELETE FROM $this->table WHERE userid=$uid AND projectid=$pid';
	$result = execute_sql($sql);
	if (!$result) {
		return $err[] = 'Error Removing User from Project ID:'.$pid;
	} else {
		return "Successfully REmoved UserID:$uid to ProjectID:$pid";
	}
}

function updateUser($uid,$pid,$perm) {
	$sql = "UPDATE $this->table SET admin = $perm WHERE userid=$uid AND projectid=$pid";
	$result = execute_sql($sql);
	if (!$result) {
		return $err[] = 'Error Updating User to '.$perm.' for Admin on Project ID:'.$pid;
	} else {
		return "Successfully Updated UserID:$uid to Admin: $perm on ProjectID:$pid";
	}
}
*/
}//Class END
?>