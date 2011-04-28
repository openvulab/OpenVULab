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
if ($_SESSION['mode'] == 'edit') {
	//Make markers to remove emptied fields
	

	
	if ($_POST['activate'] == 'true') {
		$data = array('status'=>'3');
		$editresult = $project->update($data);
		if (is_array($editresult)) {
			//set errors
			$err = $editresult;
		} else { //Set Success
			unset($project);
			$project = new Project;
			$project->init($_SESSION[pid]);
		}
	}
}
if (is_array($err)) {
	$step = $from;
}


?>