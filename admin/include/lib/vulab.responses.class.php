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
/*
File: 		vulab.responses.class.php \\v 1.0
Info:		- the Response: $response = new Response($responseid);
Author: 	Blake Edwards
Email:		electBlake@gmail.com

License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
*/
?>
<?php
class Response {

function __construct($rid=NULL) { //a.k.a Get Project
	$this->id = $rid;
	$getSQL = 'SELECT * FROM '.$GLOBALS['ESPCONFIG']['response_table']." WHERE id='$this->id'";

	$response_result = execute_sql($getSQL);
	//print_r($proj_result->fields);
	
	list(	$r['id'],
			$r['survey_id'],
			$r['submitted'],
			$r['complete'],
			$r['username'],
			$r['ip'],
			$r['vid']) = $response_result->fields;	

	
	$r = array_reverse($r);
	
	//load details
	$this->details = $r;

}

function update($data,$options=null) {
	require ESP_BASE.'admin/sanitize.php';
	global $ESPCONFIG;
	$pid = $this->id;
	if (@$data['id']) { $r[id] = sanitize($data['id']); }
	if (@$data['survey_id']) { $r[survey_id] = sanitize($data['survey_id']); }
	if (@$data['submitted']) { $r[submitted] = sanitize($data['submitted']); }
	if (@$data['complete']) { $r[complete] = sanitize($data['complete']); }
	if (@$data['username']) {$r[username] = sanitize($data['username']); }
	if (@$data['ip']) { $r[ip] = sanitize($data['ip']); }
	if (@$data['vid']) { @$r[vid] = sanitize(@$data['vid']); }
	
	
	foreach ($r as $key=>$value) {
		if ($value == 'delete') {
			$r[$key] = '';
		}
	}
/*	$r[editstamp] = time();
	
	if ($r[status] == '2') {
		$r[activestamp] = time();
	}*/
	//Generate the Update sql
	$setsql = "SET ";
	foreach ($r as $key=>$d) {
		$setsql .= "$key = '$d', ";
	}
	$setsql = substr($setsql,0,-2);
	
	$rsql = "UPDATE ".@$ESPCONFIG[response_table]." ".$setsql." WHERE id='".$this->id."'";
	//echo $rsql;
	$result = execute_sql($rsql);
	if (ErrorMsg()) $err[] = ErrorMsg();
	if (@$err) return $err;
	return true;
}

}//Class END
?>