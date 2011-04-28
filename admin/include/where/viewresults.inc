<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/

if ($_GET['pid']) {
	$project = new Project;
	$project->init($_GET['pid']);
	$presurvey = $project->details['pre_id'];
	$postsurvey = $project->details['post_id'];
	echo "<h2>View Results</h2>";
	echo "<a href='".$GLOBALS['ESPCONFIG']['ME'] .htmlentities("?where=results&sid=${presurvey}")."'>View Pre-Survey Results</a><br />";
	echo "<a href='".$GLOBALS['ESPCONFIG']['ME'] .htmlentities("?where=results&sid=${postsurvey}")."'>View Post-Survey Results</a><br />";
} else {

	echo "<div id='errors'>You didn't select a project! <ul><li><a href='javascript:history.go(-1)'>Go back...</a></li></ul></div>";
}
?>