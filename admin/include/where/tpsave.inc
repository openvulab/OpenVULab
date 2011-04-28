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
error_reporting(E_ALL);

require ESP_BASE.'admin/sanitize.php';


	$sql = "insert into `userprojectrel` values('','".sanitize($_POST['tester'])."','".sanitize($_POST['project'])."','";
	if ($_POST['admin'] == '1')
		$sql .= "Y";
	else
		$sql .= "N";
	$sql .= "')";
	$result = execute_sql($sql);
	
	$sql = "select * from `user` WHERE `userid` = '".sanitize($_POST['tester'])."'";
	$result = execute_sql($sql);
	$emailAddress = $result->fields[5];
	mail($emailAddress,"You have been Added to a Project",$result->fields[3].",\n\tYou have been added to a new Vu Labs project.");
	
	echo "<h2>The user has been added to your project!</h2>";
?>