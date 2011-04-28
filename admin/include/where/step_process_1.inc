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
//File to Save Changes and Manage the PHP of Step 1
if ($_SESSION['mode'] == 'create') {

	$newproj = new Project;

	$createresult = $newproj->create_project($_POST);
	if (is_array($createresult)) {
		//set errors
		$err = $createresult;
	} else { //Set Success
		$_SESSION[mode] = 'edit';
		unset($project);
		$project = new Project;
		$project->init($_SESSION[pid]);
	}
}
elseif ($_SESSION['mode'] == 'edit') {
	//Make markers to remove emptied fields
	
	if (!$_POST['pre']) { $_POST['pre'] = 'delete'; }
	if (!$_POST['post']) { $_POST['post'] = 'delete'; }
	if (!$_POST['pintro']) { $_POST['pintro'] = 'delete'; }
	if (!$_POST['poutro']) { $_POST['poutro'] = 'delete'; }
	if (!$_POST['pgoal']) { $_POST['pgoal'] = 'delete'; }
	if (!$_POST['purl']) { $_POST['purl'] = 'delete'; }
	if (!$_POST['pstart']) { $_POST['pstart'] = 'delete'; }
	if (!$_POST['pend']) { $_POST['pend'] = 'delete'; }
	
	
	$editresult = $project->update($_POST);
	if (is_array($editresult)) {
		//set errors
		$err = $editresult;
	} else { //Set Success
		unset($project);
		$project = new Project;
		$project->init($_SESSION[pid]);
	}
}
if (is_array($err)) {
	$step = $from;
}


?>